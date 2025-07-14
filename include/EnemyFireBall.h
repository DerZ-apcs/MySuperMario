#ifndef ENEMYFIREBALL_H
#define ENEMYFIREBALL_H
#include <raylib.h>
#include "../include/Entity.h"
#include "../include/Global.h"
#include "../include/Character.h"

class EnemyFireBall : public Entity {
private:
    float timeSpan;
    float timeSpanAcum;
    static const float maxTime;
    float currTime;
    static const float FB_SpeedX;
    bool isHoming; // Cờ bật/tắt chế độ nhắm mục tiêu
public:
    EnemyFireBall(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan, bool homing = false);
    ~EnemyFireBall();
    EntityType getEntityType() const override;
    void Update() override;
    void draw() override;
    void updateCollision() override;
    void UpdateTexture() override;
    bool isMaxTime() const;
};
#endif