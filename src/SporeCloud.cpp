#include "../include/SporeCloud.h"
#include "../include/ResourceManager.h"
#include "../include/SporeDroplet.h"
#include "../include/GameEngine.h"

const float SPORE_DROP_INTERVAL = 0.8f; // Thả một vật sau mỗi 0.8 giây
const float SPORE_INTER_DROP_DELAY = 0.2f;
const Vector2 SPORE_CLOUD_SIZE = { 64.0f, 64.0f };

SporeCloud::SporeCloud(Vector2 pos, Character* target)
    : Effect(pos, 0.0f, SPORE_CLOUD_LIFESPAN),
      target(target),
      dropTimer(SPORE_DROP_INTERVAL), // Khởi tạo bộ đếm giờ
      isFiringLeft(true),
      faceDirection(1.0f)
{
    setSize(SPORE_CLOUD_SIZE);
    gravityAvailable = false; 
    collisionAvailable = false;
    texture = RESOURCE_MANAGER.getTexture("spore_cloud");
}

void SporeCloud::Update() {
    float dt = GetFrameTime();

    if (target) {
		faceDirection = (target->getPosition().x > position.x) ? 1.0f : -1.0f;
    }

    dropTimer -= dt;

    if (dropTimer <= 0.0f) {
        if (globalGameEngine) {
            if (isFiringLeft) {
                // Lượt 1: Bắn giọt bên trái
                Vector2 dropletPos1 = { position.x + (size.x / 4.0f), position.y + size.y };
                SporeDroplet* droplet1 = new SporeDroplet(dropletPos1);
                globalGameEngine->addEffect(droplet1);

                // Đặt lại bộ đếm giờ cho lần bắn tiếp theo (bên phải) với độ trễ ngắn
                dropTimer = SPORE_INTER_DROP_DELAY;
            }
            else {
                // Lượt 2: Bắn giọt bên phải
                Vector2 dropletPos2 = { position.x + (size.x * 3.0f / 4.0f), position.y + size.y };
                SporeDroplet* droplet2 = new SporeDroplet(dropletPos2);
                globalGameEngine->addEffect(droplet2);

                // Đặt lại bộ đếm giờ cho loạt bắn tiếp theo với độ trễ dài
                dropTimer = SPORE_DROP_INTERVAL;
            }
            // Đảo cờ để lần sau bắn giọt còn lại
            isFiringLeft = !isFiringLeft;
        }
    }
    
    Effect::Update();
}

void SporeCloud::draw() {
    Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle destRec = getRect();

    // Nếu faceDirection là -1.0f, lật chiều rộng của sourceRec để lật hình ảnh
    sourceRec.width *= faceDirection;

    // Vẽ texture đã có thể được lật
    DrawTexturePro(texture, sourceRec, destRec, {0, 0}, 0.0f, Fade(WHITE, 0.8f));

    if (SETTING.getDebugMode()) {
        DrawRectangleLinesEx(getRect(), 2, VIOLET);
    }
}

EntityType SporeCloud::getEntityType() const {
    return SPORE_CLOUD;
}