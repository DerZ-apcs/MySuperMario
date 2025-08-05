#ifndef BENZAIBILL_H
#define BENZAIBILL_H

#include "../include/Enemy.h"

class BenzaiBill : public Enemy {
private:
    const float SPEED_BENZAIBILL = 100.f;
public:
    BenzaiBill(Vector2 pos, Texture2D texture, Direction direction);
    ~BenzaiBill() = default;
    ENEMY_TYPE getEnemyType() const override;
    void Update() override;
    void draw() override;
    float getScores() const override;
    void stomped() override;
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};
#endif