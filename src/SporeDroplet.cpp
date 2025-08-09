#include "../include/SporeDroplet.h"
#include "../include/ResourceManager.h"
#include "../include/GameEngine.h"

const Vector2 SPORE_DROPLET_SIZE = { 16.0f, 16.0f };
const float SPORE_DROPLET_LIFESPAN = 5.0f; // Tự hủy sau 5 giây nếu không va chạm

SporeDroplet::SporeDroplet(Vector2 pos)
    : Effect(pos, 0.0f, SPORE_DROPLET_LIFESPAN)
{
    setSize(SPORE_DROPLET_SIZE);
    gravityAvailable = true;  // QUAN TRỌNG: Vật này phải rơi xuống
    collisionAvailable = true; // Có thể va chạm với tilemap

    texture = RESOURCE_MANAGER.getTexture("spore_droplet");
}

void SporeDroplet::Update() {
    // Kiểm tra va chạm với người chơi
    if (globalGameEngine) {
        auto& players = globalGameEngine->getMultiplayers();
        for (auto& player : players) {
            if (player && !player->isImmortal() && player->getPhase() != DEAD_PHASE && player->getPhase() != CLEARLEVEL_PHASE) {
                if (CheckCollisionRecs(getRect(), player->getRect())) {
                    player->lostSuit(); // Gây sát thương cho người chơi
                    setEntityDead();    // Hủy "viên đạn" này ngay khi va chạm
                    return;
                }
            }
        }
    }

    Effect::Update();
}

void SporeDroplet::draw() {
    DrawTexture(texture, position.x, position.y, WHITE);

    if (SETTING.getDebugMode()) {
        DrawRectangleLinesEx(getRect(), 1, RED);
    }
}

EntityType SporeDroplet::getEntityType() const {
    return ENEMY_FIREBALL; 
}