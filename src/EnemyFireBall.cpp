#include "../include/EnemyFireBall.h"
#include "../include/ResourceManager.h"

const float EnemyFireBall::maxDistance = 1000.0f;
const float EnemyFireBall::FB_SpeedX = 400.0f;

EnemyFireBall::EnemyFireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan)
    : Entity(pos, sz, vel, dir, ON_GROUND, 0.1f, 3, BLACK), timeSpan(timeSpan), timeSpanAcum(0), isDestroyed(false) {
    this->texture = direction == RIGHT ? Singleton<ResourceManager>::getInstance().getTexture("EnemyFireball_RIGHT_0") :
        Singleton<ResourceManager>::getInstance().getTexture("EnemyFireball_LEFT_0");
    this->frameAcum = 0;
    this->currFrame = 0;
    this->CollNorth.setSize(Vector2{ size.x - 8, 1 });
    this->CollSouth.setSize(Vector2{ size.x - 8, 1 });
    this->CollEast.setSize(Vector2{ 1, size.y - 8 });
    this->CollWest.setSize(Vector2{ 1, size.y - 8 });
    this->updateCollision();
}

EnemyFireBall::~EnemyFireBall() {
}

void EnemyFireBall::Update() {
    if (isMaxDistance() || isDestroyed) return;

    const float deltaTime = GetFrameTime();
    frameAcum += deltaTime;
    maxFrame = 3;
    if (frameAcum >= frameTime) {
        frameAcum = 0;
        currFrame = (currFrame + 1) % (maxFrame + 1); // Đảm bảo lặp đúng số frame
    }
    timeSpanAcum += deltaTime;
    if (velocity.x > 0)
        direction = RIGHT;
    else if (velocity.x < 0)
        direction = LEFT;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    velocity.y += GRAVITY * deltaTime;

    updateCollision();
    UpdateTexture(); // Gọi UpdateTexture trong Update để đảm bảo texture luôn hợp lệ
}

void EnemyFireBall::draw() {
    if (isMaxDistance() || isDestroyed) return;
    DrawTexture(texture, position.x, position.y, WHITE);
}

void EnemyFireBall::updateCollision() {
    Entity::updateCollision();
}

void EnemyFireBall::UpdateTexture() {
    const std::string dir = direction == LEFT ? "_LEFT_" : "_RIGHT_";
    std::string textureName = "EnemyFireball" + dir + std::to_string(currFrame);
    texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
    // Kiểm tra texture hợp lệ
    if (texture.id == 0) {
        // Sử dụng texture mặc định nếu không tải được
        texture = direction == RIGHT ? Singleton<ResourceManager>::getInstance().getTexture("EnemyFireball_RIGHT_0") :
            Singleton<ResourceManager>::getInstance().getTexture("EnemyFireball_LEFT_0");
    }
}

bool EnemyFireBall::isMaxDistance() const {
    return timeSpanAcum >= timeSpan;
}

void EnemyFireBall::HandleTileCollision(const Tile tile, CollisionType Colltype) {
    if (Colltype == COLLISION_TYPE_NONE)
        return;
    switch (Colltype) {
    case COLLISION_TYPE_EAST:
        setPosition({ tile.getX() - size.x, position.y });
        velocity.x *= -1;
        break;
    case COLLISION_TYPE_NORTH:
        setPosition({ position.x, tile.getY() + tile.getHeight() });
        velocity.y = 0;
        break;
    case COLLISION_TYPE_SOUTH:
        setPosition({ position.x, tile.getY() - size.y });
        velocity.y *= -1;
        break;
    case COLLISION_TYPE_WEST:
        setPosition({ tile.getX() + tile.getWidth(), position.y });
        velocity.x *= -1;
        break;
    default:
        break;
    }
}

void EnemyFireBall::destroy() {
    isDestroyed = true;
}