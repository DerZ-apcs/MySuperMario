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

void to_json(json& j, const Character& c) {
    j = json{
        {"type", static_cast<int>(c.getCharacterType())},
        {"pos", {c.getX(), c.getY()}},
        {"vel", {c.getVelX(), c.getVelY()}},
        {"state", static_cast<int>(c.getState())},
        {"characterState", static_cast<int>(c.getCharacterState())},
        {"lives", c.getLives()},
        {"scores", c.getScores()},
        {"coins", c.getCoins()},
        {"phase", static_cast<int>(c.getPhase())},
        {"direction", static_cast<int>(c.getDir())}
    };
}

void to_json(json& j, const Enemy& e)
{
    j = json{
        {"EnemyType", static_cast<int>(e.getEnemyType())},
        {"pos", {e.getX(), e.getY()}},
        {"vel", {e.getVelX(), e.getVelY()}},
        {"state", static_cast<int>(e.getState())},
        {"scores", e.getScores()},
        {"direction", static_cast<int>(e.getDir())}
    };
}

void to_json(json& j, const Item& item)
{
    j = json{
        {"ItemType", static_cast<int>(item.getItemType())},
        {"pos", {item.getX(), item.getY()}},
        {"vel", {item.getVelX(), item.getVelY()}},
        {"direction", static_cast<int>(item.getDir()) }
    };
}

void to_json(json& j, const Blocks& b)
{
    j = json{
        {"type", static_cast<int>(b.getBlockType())},
        {"pos", {b.getX(), b.getY()}}
    };
}

void to_json(json& j, const FireBall& fb)
{
    j = json{
        {"pos", {fb.getX(), fb.getY()}},
        {"vel", {fb.getVelX(), fb.getVelY()}},
        {"direction", static_cast<int>(fb.getDir())},
        {"currtime", fb.getCurrTime()}
    };
}

void to_json(json& j, const EnemyFireBall& ef)
{
    j = json{
        {"pos", {ef.getX(), ef.getY()}},
        {"vel", {ef.getVelX(), ef.getVelY()}},
        {"direction", static_cast<int>(ef.getDir())},
        {"currtime", ef.getCurrTime()}
    };
}

void to_json(json& j, const int remainedTime, const int level)
{
    j = json{
        {"remainedTime", remainedTime},
        {"level", level}
    };
}

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
        e = new Spiny(pos, tex);
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

Item* loadItem(const json& j)
{
    
}

Blocks* loadBlocks(const json& j)
{
    
}

FireBall loadFireBall(const json& j)
{
    
}

EnemyFireBall loadEnemyFireBall(const json& j)
{
    
}


void saveMultiCharacters(const std::vector<std::unique_ptr<Character>>& multiplayers, json& j) {
    for (const auto& c : multiplayers)
        if (c) j["players"].push_back(*c);
}

void loadMultiCharacters(std::vector<std::unique_ptr<Character>>& multiplayers, const json& j) {
    multiplayers.clear();
    for (const auto& entry : j.at("players")) {
        multiplayers.push_back(loadCharacter(entry));
    }
}

void saveEnemies(const std::vector<Enemy*>& enemies, json& j)
{
    j = json::array();
    for (const Enemy* e : enemies) {
        json enemyJson;
        enemyJson["EnemyType"] = static_cast<int>(e->getEnemyType()); // You need a getType() method
        enemyJson["pos"] = { e->getX(), e->getY()};
        enemyJson["vel"] = { e->getVelX(), e->getVelY()};
        enemyJson["state"] = static_cast<int>(e->getState());
        enemyJson["direction"] = static_cast<int>(e->getDir());
        // Add more fields if needed
        j.push_back(enemyJson);
    }
}

void loadEnemies(std::vector<Enemy*>& enemies, const json& j)
{
    enemies.clear();
    for (const auto& enemyJson : j) {
        Enemy* e = loadEnemy(enemyJson);
        if (e) enemies.push_back(e);
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