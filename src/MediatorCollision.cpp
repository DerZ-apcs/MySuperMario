#include "../include/MediatorCollision.h"

void MediatorCollision::HandlePlayerWithTiles(Mario*& mario, Tile*& tile, CollisionType Colltype)
{
    if (Colltype == COLLISION_TYPE_NONE) return;
    switch (Colltype) {
    case COLLISION_TYPE_NORTH:
        mario->setPosition(Vector2{ mario->getX(), tile->getY() + tile->getHeight() });
        mario->setVelY(0);
        break;
    case COLLISION_TYPE_SOUTH:
        mario->setPosition(Vector2{ mario->getX(), tile->getY() - mario->getHeight() });
        mario->setState(ON_GROUND);
        mario->setVelY(0);
        break;
    case COLLISION_TYPE_EAST:
        mario->setPosition(Vector2{ tile->getX() - mario->getWidth(), mario->getY() });
        mario->setVelX(0);
        break;
    case COLLISION_TYPE_WEST:
        mario->setPosition(Vector2{ tile->getX() + tile->getWidth(), mario->getY() });
        mario->setVelX(0);
        break;
    default:
        break;
    }
}

void MediatorCollision::HandleFireballWithTiles(FireBall*& fireball, Tile*& tile, CollisionType Colltype)
{
    if (Colltype == COLLISION_TYPE_NONE) return;
    switch (Colltype)
    {
    case COLLISION_TYPE_NORTH:
        fireball->setPosition(Vector2{ fireball->getX(), tile->getY() + tile->getHeight() });
        fireball->setVelY(0);
        break;
    case COLLISION_TYPE_SOUTH:
        fireball->setPosition(Vector2{ fireball->getX(), tile->getY() - fireball->getHeight() });
        fireball->setVelY(fireball->getVelY() * -1);
        break;
    case COLLISION_TYPE_EAST:
        fireball->setPosition(Vector2{ tile->getX() - fireball->getWidth(), fireball->getY() });
        fireball->setVelX(fireball->getVelX() * -1);
        break;
    case COLLISION_TYPE_WEST:
        fireball->setPosition(Vector2{ tile->getX() + tile->getWidth(), fireball->getY() });
        fireball->setVelX(fireball->getVelX() * -1);
        break;
    default:
        break;
    }
}

void MediatorCollision::HandleEnemyWithMario(Enemy*& enemy, Mario*& mario, CollisionType Colltype)
{
    if (Colltype == COLLISION_TYPE_NONE) {
        return;
    }
    Koopa* koopa = dynamic_cast<Koopa*>(enemy);
    if (koopa && koopa->getState() == STATE_SHELL && koopa->getVelX() == 0 &&
        (Colltype == COLLISION_TYPE_EAST || Colltype == COLLISION_TYPE_WEST)) {
        enemy->CollisionWithCharacter(*mario, Colltype);
        return;
    }
    if (mario->getInvincibilityTimer() > 0) {
        return;
    }
    enemy->CollisionWithCharacter(*mario, Colltype);
}

//void MediatorCollision::HandleCollision(Entity* entity1, Entity* entity2)
//{
//    Mario* isMario_1 = dynamic_cast<Mario*>(entity1);
//    Mario* isMario_2 = dynamic_cast<Mario*>(entity2);
//    FireBall* isFireBall_1 = dynamic_cast<FireBall*>(entity1);
//    FireBall* isFireBall_2 = dynamic_cast<FireBall*>(entity2);
//    Tile* isTile_1 = dynamic_cast<Tile*>(entity1);
//    Tile* isTile_2 = dynamic_cast<Tile*>(entity2);
//    Enemy* isEnemy_1 = dynamic_cast<Enemy*>(entity1);
//    Enemy* isEnemy_2 = dynamic_cast<Enemy*>(entity2);
//
//    if ((isMario_1 && isTile_2) || (isMario_2 && isTile_1)) {
//        CollisionType CollType = isMario_1 ? isMario_1->CheckCollision(*isTile_2) : isMario_2->CheckCollision(*isTile_1);
//        if (isMario_1)
//            HandlePlayerWithTiles(isMario_1, isTile_2, CollType);
//        else
//            HandlePlayerWithTiles(isMario_2, isTile_1, CollType);
//    }
//    else if ((isFireBall_1 && isTile_2) || (isFireBall_2 && isTile_1)) {
//        CollisionType CollType = isFireBall_1 ? isFireBall_1->CheckCollision(*isTile_2) : isFireBall_2->CheckCollision(*isTile_1);
//        if (isFireBall_1)
//            HandleFireballWithTiles(isFireBall_1, isTile_2, CollType);
//        else
//            HandleFireballWithTiles(isFireBall_2, isTile_1, CollType);
//    }
//    else if ((isMario_1 && isEnemy_2) || (isMario_2 && isEnemy_1)) {
//        CollisionType CollType = isMario_1 ? isMario_1->CheckCollision(*isEnemy_2) : isMario_2->CheckCollision(*isEnemy_1);
//        if (isMario_1)
//            HandleEnemyWithMario(isEnemy_2, isMario_1, CollType);
//        else
//            HandleEnemyWithMario(isEnemy_1, isMario_2, CollType);
//    }
//}

void MediatorCollision::HandleCollision(Entity* entity1, Entity* entity2) {
    // Kiểm tra sớm để giảm dynamic_cast
    if (entity1 == entity2) return;

    Mario* mario = dynamic_cast<Mario*>(entity1);
    Enemy* enemy = dynamic_cast<Enemy*>(entity2);
    if (mario && enemy) {
        CollisionType collType = mario->CheckCollision(*enemy);
        if (collType != COLLISION_TYPE_NONE) {
            HandleEnemyWithMario(enemy, mario, collType);
        }
        return;
    }

    mario = dynamic_cast<Mario*>(entity2);
    enemy = dynamic_cast<Enemy*>(entity1);
    if (mario && enemy) {
        CollisionType collType = mario->CheckCollision(*enemy);
        if (collType != COLLISION_TYPE_NONE) {
            HandleEnemyWithMario(enemy, mario, collType);
        }
        return;
    }

    Tile* tile = dynamic_cast<Tile*>(entity1);
    mario = dynamic_cast<Mario*>(entity2);
    if (tile && mario) {
        CollisionType collType = mario->CheckCollision(*tile);
        if (collType != COLLISION_TYPE_NONE) {
            HandlePlayerWithTiles(mario, tile, collType);
        }
        return;
    }

    tile = dynamic_cast<Tile*>(entity2);
    mario = dynamic_cast<Mario*>(entity1);
    if (tile && mario) {
        CollisionType collType = mario->CheckCollision(*tile);
        if (collType != COLLISION_TYPE_NONE) {
            HandlePlayerWithTiles(mario, tile, collType);
        }
        return;
    }

    FireBall* fireball = dynamic_cast<FireBall*>(entity1);
    tile = dynamic_cast<Tile*>(entity2);
    if (fireball && tile) {
        CollisionType collType = fireball->CheckCollision(*tile);
        if (collType != COLLISION_TYPE_NONE) {
            HandleFireballWithTiles(fireball, tile, collType);
        }
        return;
    }

    fireball = dynamic_cast<FireBall*>(entity2);
    tile = dynamic_cast<Tile*>(entity1);
    if (fireball && tile) {
        CollisionType collType = fireball->CheckCollision(*tile);
        if (collType != COLLISION_TYPE_NONE) {
            HandleFireballWithTiles(fireball, tile, collType);
        }
        return;
    }
}