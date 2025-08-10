// Spiny.h
#ifndef SPINY_H
#define SPINY_H

#include "../include/Enemy.h"       

class Spiny : public Enemy {
protected:
    static constexpr float SPINY_SPEED = 120.0f;
    static const int SCORE_STOMP_SPINY;
public:
    Spiny(Vector2 pos, Texture2D texture);

    void Update() override;
    void draw() override;
    void UpdateTexture() override;

    void stomped() override;
    ENEMY_TYPE getEnemyType() const override;
    float getScores() const override;
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};

#endif // SPINY_H