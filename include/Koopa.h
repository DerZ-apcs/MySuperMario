#ifndef KOOPA_H
#define KOOPA_H
#include "../include/Enemy.h"

enum KoopaState {
    NORMAL_KOOPA,
    SHELL_KOOPA
};
class Koopa : public Enemy {
private:
    KoopaState koopaState;
    KOOPA_TYPE koopaType;
    float reviveTimer;
    bool isReviving; // Trạng thái rung trước khi hồi sinh
    float reviveShakeTimer; // Timer cho hiệu ứng rung
public:
    KOOPA_TYPE getKoopaType() const;
    ENEMY_TYPE getEnemyType() const;
    Koopa(Vector2 pos, Texture2D texture);
    void setKoopaType(KOOPA_TYPE type);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void attacked(Direction direction) override;
    float getScores() const override;
    void stomped();
    void kicked(Direction direction) override;
    void updateCollision() override;
};

class FlyingKoopa : public Koopa {
private:
    float jumpTimer; // Timer để kiểm soát tần suất nhảy
    float collisionTimer;
public:
    ENEMY_TYPE getEnemyType() const;
    FlyingKoopa(Vector2 pos, Texture2D texture);
    void Update() override;
    void UpdateTexture() override;
    float getScores() const override;
};
#endif