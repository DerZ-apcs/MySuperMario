#pragma once
#include "Enemy.h"
#include "Goomba.h"
#include "ParaKoopa.h"
#include "PiranhaPlant.h"
#include "FirePiranhaPlant.h"
#include "JumpingPiranhaPlant.h"
#include "Boss.h"
#include "Koopa.h"
#include "BoomBoom.h"
#include "Bullet.h"
#include "BobOmb.h"
#include "Rex.h"
#include "BanzaiBill.h"
#include "Muncher.h"
#include "Spiny.h"
#include "DryBones.h"
#include "BuzzyBeetle.h"
#include "ResourceManager.h"
#include "json.hpp"
#include <iostream>
using json = nlohmann::json;

static Texture2D loadTextureFromType(ENEMY_TYPE type) {
    switch (type) {
    case GOOMBA: return RESOURCE_MANAGER.getTexture("Goomba_RIGHT_0");
    case KOOPA: return RESOURCE_MANAGER.getTexture("Koopa_RIGHT_0");
    case PARAKOOPA: return RESOURCE_MANAGER.getTexture("ParaKoopa_RIGHT_0");
    case PIRANHA: return RESOURCE_MANAGER.getTexture("PiranhaPlant_OPEN");
    case BULLET: return RESOURCE_MANAGER.getTexture("Bullet");
    case BANZAIBILL: return RESOURCE_MANAGER.getTexture("BanzaiBill_LEFT_0");
    case BOBOMB: return RESOURCE_MANAGER.getTexture("BobOmb_LEFT_0");
    case REX: return RESOURCE_MANAGER.getTexture("Rex_RIGHT_0");
    case MUNCHER: return RESOURCE_MANAGER.getTexture("Muncher");
    case SPINY: return RESOURCE_MANAGER.getTexture("Spiny_RIGHT_0");
    case DRYBONES: return RESOURCE_MANAGER.getTexture("DryBones_LEFT_0");
    case BUZZYBEETLE: return RESOURCE_MANAGER.getTexture("BuzzyBeetle_RIGHT_0");
	case BOSS: return RESOURCE_MANAGER.getTexture("BoomBoom_walk_right_1");
    default:
        std::cerr << "Unknown enemy type for texture loading\n";
        return {};
    }
}
class EnemyFactory {
public:
    static Enemy* createEnemy(const json& enemyJson) {
        if (!enemyJson.contains("EnemyType") || !enemyJson.contains("pos")) {
            std::cerr << "Invalid enemy json\n";
            return nullptr;
        }

        ENEMY_TYPE type = static_cast<ENEMY_TYPE>(enemyJson["EnemyType"].get<int>());
        Vector2 pos = { enemyJson["pos"][0], enemyJson["pos"][1] };
        Texture2D tex = loadTextureFromType(type);
        Enemy* e = nullptr;

        switch (type) {
        case GOOMBA: {
            GOOMBA_TYPE gt = static_cast<GOOMBA_TYPE>(enemyJson["goombaType"].get<int>());
            if (gt == NORMAL_GOOMBA)
                e = new Goomba(pos, tex);
            else if (gt == FLYING_GOOMBA)
                e = new FlyingGoomba(pos, RESOURCE_MANAGER.getTexture("FlyingGoomba_RIGHT_0"));
            break;
        }
        case KOOPA: {
            KOOPA_TYPE kt = static_cast<KOOPA_TYPE>(enemyJson["koopaType"].get<int>());
            if (kt == GREEN_KOOPA)
                e = new GreenKoopa(pos, tex);
            else if (kt == RED_KOOPA)
                e = new RedKoopa(pos, tex);
            else if (kt == BLUE_KOOPA)
                e = new BlueKoopa(pos, tex);
            else
                e = new YellowKoopa(pos, tex);
            break;
        }
        case PARAKOOPA: {
            PARAKOOPA_TYPE pt = static_cast<PARAKOOPA_TYPE>(enemyJson["paraKoopaType"].get<int>());
            if (pt == GREEN_PARAKOOPA)
                e = new ParaKoopaGreen(pos, tex);
            else if (pt == RED_PARAKOOPA)
                e = new ParaKoopaRed(pos, tex);
            else if (pt == BLUE_PARAKOOPA)
                e = new ParaKoopaBlue(pos, tex);
            else
                e = new ParaKoopaYellow(pos, tex);
            break;
        }
        case PIRANHA: {
            PIRANHA_TYPE pt = static_cast<PIRANHA_TYPE>(enemyJson["piranhaType"].get<int>());
            if (pt == NORMAL_PIRANHA)
                e = new PiranhaPlant(pos, tex);
            else if (pt == FIRE_PIRANHA)
                e = new FirePiranhaPlant(pos, tex);
            else if (pt == RAPIDFIRE_PIRANHA)
                e = new RapidFirePiranha(pos, tex);
			else if (pt == HOMING_PIRANHA)
                e = new HomingFirePiranha(pos, tex);
			else if (pt == JUMPING_PIRANHA)
				e = new JumpingPiranhaPlant(pos, tex);
            break;
        }
        case BULLET: {
            BULLET_TYPE bt = static_cast<BULLET_TYPE>(enemyJson["bulletType"].get<int>());
            if (bt == NORMAL_BULLET)
                e = new Bullet(pos, tex);
            else
                e = new FireBullet(pos, tex);
            break;
        }
		case BANZAIBILL: {
			e = new BanzaiBill(pos, tex);
			break;
		}
        case SHELL: {
            Koopa* koopa = new Koopa(pos, tex);
            koopa->setKoopaState(SHELL_KOOPA);
            e = koopa;
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
            break;
        }

        if (e) {
            e->loadEntity(enemyJson);
        }
        return e;
    }
};


