#include "../include/SporeCloud.h"
#include "../include/ResourceManager.h"

// Các hằng số để dễ dàng điều chỉnh hành vi
const float SPORE_CLOUD_LIFESPAN = 5.0f;
const float SPORE_CLOUD_DAMAGE_INTERVAL = 1.0f;
const Vector2 SPORE_CLOUD_SIZE = { 64.0f, 64.0f };

// SỬA ĐỔI HÀM KHỞI TẠO
SporeCloud::SporeCloud(Vector2 pos)
    : Effect(pos, 0.0f, SPORE_CLOUD_LIFESPAN),
    damageCooldown(0.0f)
{
    
    setSize(SPORE_CLOUD_SIZE);
    gravityAvailable = false;
    collisionAvailable = false;

    texture = RESOURCE_MANAGER.getTexture("spore_cloud");
}

void SporeCloud::Update() {
    float dt = GetFrameTime();

    if (damageCooldown > 0.0f) {
        damageCooldown -= dt;
    }

    if (damageCooldown <= 0.0f) {
        auto& players = globalGameEngine->getMultiplayers();
        for (auto& player : players) {
            if (player && !player->isImmortal() && player->getPhase() != DEAD_PHASE && player->getPhase() != CLEARLEVEL_PHASE) {
                if (CheckCollisionRecs(getRect(), player->getRect())) {
                    // Gây sát thương cho người chơi
                    player->lostSuit();
                    // Đặt lại thời gian hồi
                    damageCooldown = SPORE_CLOUD_DAMAGE_INTERVAL;
                    // Chỉ gây sát thương cho một người chơi mỗi lần kiểm tra để tránh lỗi
                    break;
                }
            }
        }
    }

    Effect::Update();
}

void SporeCloud::draw() {
    // Vẽ texture với hiệu ứng mờ dần để trông giống đám mây/khí độc
    DrawTexture(texture, position.x, position.y, Fade(WHITE, 0.7f));

    // Bật dòng này để debug, xem hitbox của đám mây
    if (SETTING.getDebugMode()) {
        DrawRectangleLinesEx(getRect(), 2, VIOLET);
    }
}

EntityType SporeCloud::getEntityType() const {
    return SPORE_CLOUD;
}