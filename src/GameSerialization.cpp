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

std::unique_ptr<Enemy> loadEnemy(const json& j)
{
    ENEMY_TYPE type = static_cast<ENEMY_TYPE>(j.at("EnemyType").get<int>());
    std::unique_ptr<Enemy> e;
    switch (type) {
    case GOOMBA:
        e = std::make_unique<Goomba>();
        break;
    case KOOPA:
        e = std::make_unique<Koopa>();
        break;
    case PIRANHA:
        e = std::make_unique<PiranhaPlant>();
        break;
    case BULLET:
        e = std::make_unique<Bullet>();
        break;
    case SHELL:
        e = make_unique<Koopa>();
        break;
    case BOBOMB:
        e = make_unique<BobOmb>();
        break;
    case REX:
        e = make_unique<Rex>();
        break;
    case MUNCHER:
        e = make_unique<Muncher>();
        break;
    case SPINY:
        e = make_unique<Spiny>();
        break;
    case DRYBONES:
        e = make_unique<DryBones>();
        break;
    case BUZZYBEETLE:
        e = make_unique<BuzzyBeetle>();
        break;
    default:
        std::cerr << "Unknown enemy type\n";
        return nullptr;
    }
    e->setPosition({ j.at("pos")[0], j.at("pos")[1] });
    e->setVel({ j.at("vel")[0], j.at("vel")[1] });
    e->setState(static_cast<EntityState>(j.at("state").get<int>()));


    return e;
    
}

std::unique_ptr<Item> loadItem(const json& j)
{
    
}

std::unique_ptr<Blocks> loadBlocks(const json& j)
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

void saveEnemies(const std::vector<Enemy> enemies, json& j)
{
}

void loadEnemies(std::vector<Enemy> enemies, const json& j)
{
}
