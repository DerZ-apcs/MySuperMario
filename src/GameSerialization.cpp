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
    }
}


void saveEnemies(const std::vector<Enemy*>& enemies, json& j)
{
    j = json::array();
    for (Enemy* e : enemies) {
        if (!e) continue;
        json enemyJson;
        enemyJson["EnemyType"] = e->getEnemyType();
        e->saveEntity(enemyJson);
        j.push_back(enemyJson);
    }
}

void loadEnemies(std::vector<Enemy*>& enemies, const json& j)
{
    for (Enemy* e : enemies) {
        delete e;
    }
    enemies.clear();
    // load new enemies
    for (const auto& enemyJson : j) {
        ENEMY_TYPE type = static_cast<ENEMY_TYPE>(enemyJson["EnemyType"].get<int>());
        Enemy* e = nullptr;
        Vector2 pos = { enemyJson["pos"][0], enemyJson["pos"][1] };
        Texture2D tex = loadTextureFromType(type);
        switch (type) {
        case GOOMBA: {
            GOOMBA_TYPE type = static_cast<GOOMBA_TYPE>(enemyJson["goombaType"].get<int>());
            if (type == NORMAL_GOOMBA)
                e = new Goomba(pos, tex);
            else if (type == FLYING_GOOMBA)
                e = new FlyingGoomba(pos, RESOURCE_MANAGER.getTexture("FlyingGoomba_RIGHT_0"));
            break;
        }
        case KOOPA: {
            KOOPA_TYPE type = static_cast<KOOPA_TYPE>(enemyJson["koopaType"].get<int>());
            if (type == GREEN_KOOPA)
                e = new GreenKoopa(pos, tex);
            else if (type == RED_KOOPA)
                e = new RedKoopa(pos, tex);
            else if (type == BLUE_KOOPA)
                e = new BlueKoopa(pos, tex);
            else
                e = new YellowKoopa(pos, tex);
            break;
        }
        case PARAKOOPA: {
            PARAKOOPA_TYPE type = static_cast<PARAKOOPA_TYPE>(j["paraKoopaType"].get<int>());
            if (type == GREEN_PARAKOOPA)
                e = new ParaKoopaGreen(pos, tex);
            else if (type == RED_PARAKOOPA)
                e = new ParaKoopaRed(pos, tex);
            else if (type == BLUE_PARAKOOPA)
                e = new ParaKoopaBlue(pos, tex);
            else
                e = new ParaKoopaYellow(pos, tex);
            break;
        }
        case PIRANHA: {
            PIRANHA_TYPE type = static_cast<PIRANHA_TYPE>(j["piranhaType"].get<int>());
            if (type == NORMAL_PIRANHA)
                e = new PiranhaPlant(pos, tex);
            else if (type == FIRE_PIRANHA)
                e = new FirePiranhaPlant(pos, tex);
            else if (type == RAPIDFIRE_PIRANHA)
                e = new RapidFirePiranha(pos, tex);
            else 
                e = new HomingFirePiranha(pos, tex);
            break;
        }
        case BULLET: {
            BULLET_TYPE type = static_cast<BULLET_TYPE>(j["bulletType"].get<int>());
            if (type == NORMAL_BULLET)
                e = new Bullet(pos, tex);
            else
                e = new FireBullet(pos, tex);
            break;
        }
        case SHELL: {
            e = new Koopa(pos, tex);
            dynamic_cast<Koopa*>(e)->setKoopaState(SHELL_KOOPA);
            break;  // or Shell if different class
        }
        case BOBOMB: e = new BobOmb(pos, tex); break;
        case REX: e = new Rex(pos, tex); break;
        case MUNCHER: e = new Muncher(pos, tex); break;
        case SPINY: e = new Spiny(pos, tex); break;
        case DRYBONES: e = new DryBones(pos, tex); break;
        case BUZZYBEETLE: e = new BuzzyBeetle(pos, tex); break;
        default:
            std::cerr << "Unknown enemy type\n";
            continue;
        }
        if (e) {
            e->loadEntity(enemyJson);
            enemies.push_back(e);
        }
    }
}
void saveTileGrids(const std::vector<std::vector<Blocks*>>& tileGrid, json& j)
{
    j = json::array();

    for (size_t y = 0; y < tileGrid.size(); ++y) {
        for (size_t x = 0; x < tileGrid[y].size(); ++x) {
            Blocks* block = tileGrid[y][x];
            if (!block) continue;

            json blockJson;
            blockJson["x"] = x;
            blockJson["y"] = y;
            blockJson["blockType"] = static_cast<int>(block->getBlockType());
            block->saveEntity(blockJson["data"]);

            j.push_back(blockJson);
        }
    }
    cout << "Saved blocks: " << j.size() << '\n';
}


void loadTileGrids(std::vector<std::vector<Blocks*>>& tileGrid, const json& j)
{
    // Clear old grid
    for (auto& row : tileGrid)
        for (Blocks*& block : row)
            delete block;
    tileGrid.clear();

    // Determine max width/height from saved data
    size_t maxY = 0, maxX = 0;
    for (const auto& blockJson : j) {
        maxX = std::max(maxX, static_cast<size_t>(blockJson["x"]));
        maxY = std::max(maxY, static_cast<size_t>(blockJson["y"]));
    }
    
    // Resize grid
    tileGrid.resize(maxY + 1);
    for (auto& row : tileGrid)
        row.resize(maxX + 1, nullptr);

    // Rebuild blocks
    for (const auto& blockJson : j) {
        int x = blockJson["x"];
        int y = blockJson["y"];
        BLOCK_TYPE type = static_cast<BLOCK_TYPE>(blockJson["blockType"]);
        Vector2 pos = { (float)x * 32, (float)y * 32 };
        Blocks* block = BlockFactory::getInstance().createBlock(type, pos);
        if (block)
            block->loadEntity(blockJson["data"]);
        tileGrid[y][x] = block;
    }
}

void loadItems(std::vector<Item*>& items, const json& j) {
    items.clear();
    for (const auto& entry : j) {
        ITEM_TYPE type = static_cast<ITEM_TYPE>(entry.at("itemType").get<int>());
        Vector2 pos = { entry["pos"][0], entry["pos"][1] };
        Direction dir = static_cast<Direction>(entry["direction"].get<int>());
        int subType = entry["subType"];
        std::cout << "type: " << static_cast<int>(type)
            << " pos: (" << pos.x << ", " << pos.y << ")"
            << " dir: " << static_cast<int>(dir)
            << " subtype: " << subType << std::endl;

        Item* item = ItemFactory::getInstance().createItem(type, pos, dir, subType);
        if (!item) {
            std::cerr << "Item creation failed!" << std::endl;
            continue;
        }
        item->loadEntity(entry);
        items.push_back(item);
    }
}
void saveItems(const std::vector<Item*>& items, json& j) {
    j = json::array(); // Start with an empty array
    for (Item* item : items) {
        if (!item) continue;
        json itemJson;
        itemJson["itemType"] = static_cast<int>(item->getItemType()); // Store item type
        item->saveEntity(itemJson); // Let item serialize itself
        j.push_back(itemJson);
    }
}

static Texture2D loadTextureFromType(ENEMY_TYPE type) {
    std::string tex;
    switch (type) {
    case GOOMBA:
        tex = "Goomba_LEFT_0";
        break;
    case KOOPA:
        tex = "Koopa_LEFT_0";
        break;
    case BULLET:
        tex = "Bullet_LEFT_0";
        break;
    case REX:
        tex = "Rex_LEFT_0";
        break;
    case PIRANHA:
        tex = "PiranhaPlant_0";
        break;
    case SHELL:
        tex = "KoopaShell_LEFT_0";
        break;
    case MUNCHER:
        tex = "Muncher_0";
        break;
    case BOBOMB:
        tex = "BobOmb_LEFT_0";
        break;
    case SPINY:
        tex = "Spiny_LEFT_0";
        break;
    case BUZZYBEETLE:
        tex = "BuzzyBeetle_LEFT_0";
        break;
    case DRYBONES:
        tex = "DryBones_LEFT_0";
        break;
    default:
        tex = "Unknown_Enemy";
        break;
    }
    return RESOURCE_MANAGER.getTexture(tex.c_str());
}