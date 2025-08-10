#ifndef REX_H
#define REX_H
#include "../include/Enemy.h"

enum RexState {
    REX_NORMAL,
    REX_COMPRESSED
};

class Rex : public Enemy {
private:
    RexState rexState;
    float detectMarioRange;
public:
    float getScores() const override;
    ENEMY_TYPE getEnemyType() const override;
    Rex(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void updateCollision() override;
    void stomped() override;
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};

#endif