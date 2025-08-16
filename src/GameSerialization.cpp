#include "../include/GameSerialization.h"
#include "Koopa.h"
#include "ParaKoopa.h"
#include "Goomba.h"
#include "FirePiranhaPlant.h"
#include "PiranhaPlant.h"
#include "Spiny.h"
#include "DryBones.h"
#include "Rex.h"
#include "BobOmb.h"
#include "Bullet.h"
#include "Shell.h"
#include "BuzzyBeetle.h"
#include "Muncher.h"
#include "ItemFactory.h"
#include "BlockFactory.h"
#include "EnemyFactory.h"

void saveMultiCharacters(const std::vector<std::unique_ptr<Character>>& multiplayers, json& j) {
    j["players"] = json::array();
    for (const auto& c : multiplayers) {
        if (!c) continue;
        json charJson;
        charJson["characterType"] = c->getCharacterType(); // So we know what derived class to load
        c->saveEntity(charJson);
        j["players"].push_back(charJson);
    }
}

void loadMultiCharacters(std::vector<std::unique_ptr<Character>>& multiplayers, const json& j) {
    multiplayers.clear();
    for (const auto& entry : j.at("players")) {
        CharacterType type = static_cast<CharacterType>(entry.at("characterType").get<int>());
        Character* c = nullptr; // You should have a factory for this
        if (type == MARIO)
            c = new Mario();
        else if (type == LUIGI)
            c = new Luigi();
        else if (type == PEACH)
            c = new Peach();
        else if (type == TOAD)
            c = new Toad();
        else if (type == MARISA)
            c = new Marisa();
        c->loadEntity(entry);
        multiplayers.emplace_back(c); // Wrap raw pointer into unique_ptr
        std::cout << "Loaded player position: " << c->getPosition().x << ", " << c->getPosition().y << "\n";
    }
}


void saveEnemies(const std::vector<Enemy*>& enemies, json& j)
{
    j["enemies"] = json::array();
    for (Enemy* e : enemies) {
        if (!e || e->isDead()) continue;
        json enemyJson;
        enemyJson["EnemyType"] = e->getEnemyType();
        e->saveEntity(enemyJson);
        j["enemies"].push_back(enemyJson);
    }
}

void loadEnemies(std::vector<Enemy*>& enemies, const json& j)
{
    for (Enemy* e : enemies) {
        delete e;
    }
    enemies.clear();
    if (!j.contains("enemies")) return;
    // load new enemies
    for (const auto& enemyJson : j["enemies"]) {
        Enemy* e = EnemyFactory::createEnemy(enemyJson);
        if (e) enemies.push_back(e);
		else {
			std::cerr << "Failed to create enemy from JSON: " << enemyJson.dump() << std::endl;
		}
    }
}

void saveItems(const std::vector<Item*>& items, json& j) {
    j["items"] = json::array(); // Start with an empty array
    for (Item* item : items) {
        if (!item || item->isDead()) continue;
        json itemJson;
        itemJson["itemType"] = static_cast<int>(item->getItemType()); // Store item type
        item->saveEntity(itemJson); // Let item serialize itself
        j["items"].push_back(itemJson);
    }
}

void loadItems(std::vector<Item*>& items, const json& j) {
    for (Item* item : items) {
        delete item; // Clean up old items
    }
    items.clear();
	if (!j.contains("items")) return; // No items to load
    for (const auto& entry : j["items"]) {
        if (!entry.contains("itemType") || !entry.contains("pos")) {
            std::cerr << "Invalid item entry in JSON: " << entry.dump() << std::endl;
            continue; // Skip invalid entries
        }
        ITEM_TYPE type = static_cast<ITEM_TYPE>(entry.at("itemType").get<int>());
        Vector2 pos = { entry["pos"][0], entry["pos"][1] };
        Direction dir = RIGHT; // default nếu không có
        if (entry.contains("direction")) {
            dir = static_cast<Direction>(entry["direction"].get<int>());
        }
        int subType = entry.contains("subType") ? entry["subType"].get<int>() : 0;

        Item* item = ItemFactory::getInstance().createItem(type, pos, dir, subType);
        if (!item) {
            std::cerr << "Item creation failed!" << std::endl;
            continue;
        }
        item->loadEntity(entry);
        items.push_back(item);
    }
}

void saveTileGrids(const std::vector<std::vector<Blocks*>>& tileGrid, json& j)
{
    j["tileGrids"] = json::array();

    for (size_t y = 0; y < tileGrid.size(); ++y) {
        for (size_t x = 0; x < tileGrid[y].size(); ++x) {
            Blocks* block = tileGrid[y][x];
            if (!block) continue;
			BLOCK_TYPE type = block->getBlockType();
			if (isBasisBlock(type)) continue; // Skip basis blocks

            json blockJson;
            blockJson["x"] = x;
            blockJson["y"] = y;
            blockJson["blockType"] = static_cast<int>(type);
            block->saveEntity(blockJson["data"]);

            j["tileGrids"].push_back(blockJson);
        }
    }
    cout << "Saved special blocks: " << j["tileGrids"].size() << '\n';
}


void loadTileGrids(std::vector<std::vector<Blocks*>>& tileGrid, const json& j)
{
    // Clear old basis grid
    if (!j.contains("tileGrids")) {
        cout << "No tile grids found in JSON." << endl;
        return; // No tile grids to load
    }

    for (auto& row : tileGrid)
        for (Blocks*& block : row) {
			if (block && !isBasisBlock(block->getBlockType())) {
				delete block; // Delete only non-basis blocks
                block = nullptr;
			}
        }

    // Rebuild special blocks
    for (const auto& blockJson : j["tileGrids"]) {
        int x = blockJson["x"];
        int y = blockJson["y"];
        BLOCK_TYPE type = static_cast<BLOCK_TYPE>(blockJson["blockType"]);
        Vector2 pos = { (float)x * 32, (float)y * 32 };
        Blocks* block = BlockFactory::getInstance().createBlock(type, pos);
        if (block) {
            block->loadEntity(blockJson["data"]);
            // giu nguyen grid layput goc, chi overwrite vao cho can
            if (y < tileGrid.size() && x < tileGrid[y].size()) {
                if (tileGrid[y][x] && !isBasisBlock(tileGrid[y][x]->getBlockType())) {
                    delete tileGrid[y][x];
                } 
				tileGrid[y][x] = block; // Assign new block
			}
            else {
                std::cerr << "Block position out of bounds: (" << x << ", " << y << ")" << std::endl;
                delete block; // Clean up if out of bounds
            }
        }      
    }
    cout << "Loaded JSON block count: " << j.size() << endl;
}

bool isBasisBlock(BLOCK_TYPE type)
{
	return (type == SOLIDBLOCK || type == FLOOR ||
		type == CLOUDBLOCK || type == NOTEBLOCK || 
        type == DECOR || type == CANNON || 
        type == ROTATINGBLOCK);
}

