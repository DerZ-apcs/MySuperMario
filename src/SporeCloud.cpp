#include "../include/SporeCloud.h"
#include "../include/ResourceManager.h"
#include "../include/SporeDroplet.h"
#include "../include/GameEngine.h"

const float SPORE_DROP_INTERVAL = 0.8f; // Thả một vật sau mỗi 0.8 giây
const Vector2 SPORE_CLOUD_SIZE = { 64.0f, 64.0f };

SporeCloud::SporeCloud(Vector2 pos)
    : Effect(pos, 0.0f, SPORE_CLOUD_LIFESPAN),
    dropTimer(SPORE_DROP_INTERVAL) // Khởi tạo bộ đếm giờ
{
    setSize(SPORE_CLOUD_SIZE);
    gravityAvailable = false; 
    collisionAvailable = false;
    texture = RESOURCE_MANAGER.getTexture("spore_cloud");
}

void SporeCloud::Update() {
    float dt = GetFrameTime();
    dropTimer -= dt;

    // Khi bộ đếm giờ kết thúc, hãy thả một vật mới
    if (dropTimer <= 0.0f) {
        if (globalGameEngine) {
            // Vị trí thả là ở dưới trung tâm của đám mây
            Vector2 dropletPos = { position.x + (size.x / 2.0f), position.y + size.y };
            SporeDroplet* droplet = new SporeDroplet(dropletPos);
            globalGameEngine->addEffect(droplet);
        }

        // Đặt lại bộ đếm giờ cho lần thả tiếp theo
        dropTimer = SPORE_DROP_INTERVAL;
    }

    Effect::Update();
}

void SporeCloud::draw() {
    // Giữ nguyên logic vẽ
    DrawTexture(texture, position.x, position.y, Fade(WHITE, 0.8f));
    if (SETTING.getDebugMode()) {
        DrawRectangleLinesEx(getRect(), 2, VIOLET);
    }
}

EntityType SporeCloud::getEntityType() const {
    return SPORE_CLOUD;
}