#include "../include/GameSerialization.h"
#include "Koopa.h"
#include "Goomba.h"
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


std::unique_ptr<Character> loadCharacter(const json& j) {
    CharacterType type = static_cast<CharacterType>(j.at("type").get<int>());

    std::unique_ptr<Character> c;
    if (type == CharacterType::MARIO)
        c = std::make_unique<Mario>();
    else if (type == LUIGI)
        c = std::make_unique<Luigi>();
    else if (type == MARISA)
        c = std::make_unique<Marisa>();
    else if (type == TOAD)
        c = std::make_unique<Toad>();
    else if (type == PEACH)
        c = std::make_unique<Peach>();

    c->setPosition({ j.at("pos")[0], j.at("pos")[1] });
    c->setVel({ j.at("vel")[0], j.at("vel")[1] });
    c->setCharacterState(static_cast<CharacterState>(j.at("state").get<int>()));
    c->setLives(j.at("lives").get<int>());
    c->setScores(j.at("scores").get<int>());
    c->setCoins(j.at("coins").get<int>());
    c->setPhase(static_cast<Phase>(j.at("phase").get<int>()));
    return c;
}

Enemy* loadEnemy(const json& j)
{
    ENEMY_TYPE type = static_cast<ENEMY_TYPE>(j.at("EnemyType").get<int>());
    Enemy* e = nullptr;
    Vector2 pos = { j["pos"][0], j["pos"][1] };
    Texture2D tex = loadTextureFromType(type);
    switch (type) {
    case GOOMBA:
        e = new Goomba(pos, tex);
        break;
    case KOOPA:
        e = new Koopa(pos, tex);
        break;
    case PIRANHA:
        e = new PiranhaPlant(pos, tex);
        break;
    case BULLET:
        e = new Bullet(pos, tex);
        break;
    case SHELL:
        e = new Koopa(pos, tex);
        dynamic_cast<Koopa*>(e)->setKoopaState(SHELL_KOOPA);
        break;
    case BOBOMB:
        e = new BobOmb(pos, tex);
        break;
    case REX:
        e = new Rex(pos, tex);
        break;
    case MUNCHER:
        e = new Muncher(pos, tex);
        break;
    case SPINY:
        //e = new Spiny(pos, tex);
        break;
    case DRYBONES:
        e = new DryBones(pos, tex);
        break;
    case BUZZYBEETLE:
        e = new BuzzyBeetle(pos, tex);
        break;
    default:
        std::cerr << "Unknown enemy type\n";
        return nullptr;
    }
    if (e) {
        e->setPosition({ j.at("pos")[0], j.at("pos")[1] });
        e->setVel({ j.at("vel")[0], j.at("vel")[1] });
        e->setState(static_cast<EntityState>(j.at("state").get<int>()));
        e->setDirection(static_cast<Direction>(j.at("direction").get<int>()));
    }
    return e;
    
}

void saveMultiCharacters(const std::vector<std::unique_ptr<Character>>& multiplayers, json& j) {
    j["players"] = json::array();
    for (const auto& c : multiplayers) {
        if (!c) continue;
        json charJson;
        charJson["characterType"] = c->getCharacterType();
        c->saveEntity(charJson);
        j["players"].push_back(charJson);
    }
}

void loadMultiCharacters(std::vector<std::unique_ptr<Character>>& multiplayers, const json& j) {
    multiplayers.clear();
    for (const auto& entry : j.at("players")) {
        CharacterType type = static_cast<CharacterType>(entry.at("characterType"));
        Character* c = nullptr;
        if (type == MARIO)
            c = new Mario();
        else if (type == LUIGI)
            c = new Luigi();
        else if (type == PEACH)
            c = new Peach();
        else if (type == TOAD)
            c = new Toad();
        else if (type == MARISA)
            c = new Marisa;
        c->loadEntity(entry);
        multiplayers.emplace_back(c);// Wrap raw pointer into unique_ptr
    }
}

void saveEnemies(const std::vector<Enemy*>& enemies, json& j)
{
    j = json::array();
    for (Enemy* e : enemies) {
        if (!e) continue;
        json enemyJson;
        enemyJson["enemyType"] = e->getEnemyType();
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
        ENEMY_TYPE type = static_cast<ENEMY_TYPE>(enemyJson["enemyType"].get<int>());
        Enemy* e = nullptr;
        Vector2 pos = { enemyJson["pos"][0], enemyJson["pos"][1] };
        Texture2D tex = loadTextureFromType(type);
        switch (type) {
        case GOOMBA: e = new Goomba(pos, tex); break;
        case KOOPA: e = new Koopa(pos, tex); break;
        case PIRANHA: e = new PiranhaPlant(pos, tex); break;
        case BULLET: e = new Bullet(pos, tex); break;
        case SHELL: {
            e = new Koopa(pos, tex); 
            dynamic_cast<Koopa*>(e)->setKoopaState(SHELL_KOOPA);
            break;
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

void saveItems(const std::vector<Item*> items, json& j)
{
    j = json::array();
    for (Item* i : items) {
        if (!i) continue;
        json itemJson;
        itemJson["itemType"] = static_cast<int>(i->getItemType());
        i->saveEntity(itemJson);
        j.push_back(itemJson);
    }
}

void loadItems(std::vector<Item*>& items, const json& j)
{
    items.clear();
    for (const auto& entry : j) {
        ITEM_TYPE type = static_cast<ITEM_TYPE>(entry.at("itemType").get<int>());
        Vector2 pos = { entry["pos"][0], entry["pos"][1] };
        int subType = entry["subType"];
        Direction dir = static_cast<Direction>(entry.at("direction").get<int>());
        Item* item = ItemFactory::getInstance().createItem(type, pos, dir, subType);
        if (!item) continue;
        item->loadEntity(entry);
        items.push_back(item);
    }
}

void saveTileGrids(const std::vector<std::vector<Blocks*>> tileGrid, json& j)
{
    j = json::array();
   /* for (const auto& row : tileGrid) {
        json rowJson = json::array();
        for (Blocks* block : row) {
            if (!block) {
                continue;
            }
            json blockJson;
            blockJson["blockType"] = static_cast<int>(block->getBlockType());
            block->saveEntity(blockJson);
            rowJson.push_back(blockJson);
        } 
        j.push_back(rowJson);
    }*/
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
}

void loadTileGrids(std::vector<std::vector<Blocks*>>& tileGrid, const json& j)
{
    //tileGrid.clear();
    //for (const auto& rowJson : j) {
    //    std::vector<Blocks*> row;
    //    for (const auto& blockJson : rowJson) {
    //        if (blockJson.is_null()) {
    //            row.push_back(nullptr);
    //        }
    //        else {
    //            BLOCK_TYPE type = static_cast<BLOCK_TYPE>(blockJson.at("blockType").get<int>());
    //            Vector2 pos = { blockJson["pos"][0], blockJson["pos"][1] };
    //            Blocks* block = BlockFactory::getInstance().createBlock(type, pos); // Factory function
    //            if (block) {
    //                block->loadEntity(blockJson);
    //            }
    //            row.push_back(block);
    //        }
    //    }
    //    tileGrid.push_back(std::move(row));
    //}
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
        Vector2 pos = { (float)32 * x, (float)32 * y };
        Blocks* block = BlockFactory::getInstance().createBlock(type, pos);
        if (block)
            block->loadEntity(blockJson["data"]);

        tileGrid[y][x] = block;
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