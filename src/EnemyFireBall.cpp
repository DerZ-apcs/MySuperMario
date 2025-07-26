#include "../include/EnemyFireBall.h"
#include "../include/ResourceManager.h"
#include "../include/Game.h"
#include <raymath.h>

const float EnemyFireBall::maxDistance = 1000.0f;
const float EnemyFireBall::FB_SpeedX = 400.0f;

EnemyFireBall::EnemyFireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan, Mario* mario, bool homing)
    : Entity(pos, sz, vel, dir, ON_GROUND, 0.1f, 3, BLACK), timeSpan(timeSpan), timeSpanAcum(0), isDestroyed(false), mario(mario), isHoming(homing) {
    this->texture = direction == RIGHT ? Singleton<ResourceManager>::getInstance().getTexture("Goomba_RIGHT_0") :
        Singleton<ResourceManager>::getInstance().getTexture("Goomba_LEFT_0");
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
        currFrame = (currFrame + 1) % (maxFrame + 1);
    }
    timeSpanAcum += deltaTime;

    if (isHoming && mario) {
        Vector2 toMario = Vector2Subtract(mario->getPosition(), position);
        float homingStrength = 0.1f; // Sức mạnh nhắm mục tiêu
        Vector2 targetVel = Vector2Scale(Vector2Normalize(toMario), FB_SpeedX);
        velocity = Vector2Lerp(velocity, targetVel, homingStrength);
    }

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    velocity.y += GRAVITY * deltaTime;

    if (velocity.x > 0) direction = RIGHT;
    else if (velocity.x < 0) direction = LEFT;

    updateCollision();
    UpdateTexture();
}

void EnemyFireBall::draw() {
    if (isMaxDistance() || isDestroyed) return;
    DrawTexture(texture, position.x, position.y, WHITE);
}

void EnemyFireBall::updateCollision() {
    Entity::updateCollision();

    if (mario && !isDestroyed) {
        Rectangle fbRec = { position.x, position.y, size.x, size.y };
        Rectangle mRec = { mario->getPosition().x,
                               mario->getPosition().y,
                               mario->getSize().x,   // or mario->getWidth()
                               mario->getSize().y }; // or mario->getHeight()
        if (CheckCollisionRecs(fbRec, mRec)) {
            mario->TakeDamage();    // inflict damage
            destroy();              // remove the fireball
        }
    }
}

void EnemyFireBall::UpdateTexture() {
    const std::string dir = direction == LEFT ? "_LEFT_" : "_RIGHT_";
    std::string textureName = "EnemyFireball" + dir + std::to_string(currFrame);
    texture = Singleton<ResourceManager>::getInstance().getTexture(textureName);
    if (texture.id == 0) {
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

void EnemyFireBall::SetTexture(const Texture2D& tex) {
    texture = tex;
}

void EnemyFireBall::destroy() {
    isDestroyed = true;
}