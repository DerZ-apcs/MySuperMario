#ifndef MUNCHER_H
#define MUNCHER_H

#include "../include/Enemy.h"
#include "../include/ResourceManager.h"

class Muncher : public Enemy {
private:
    const float animationSpeed = 0.25f;

public:
    Muncher(Vector2 pos, Texture2D texture);
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void stomped() override;
    float getScores() const override;
    ENEMY_TYPE getEnemyType() const override;    
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
    
};

#endif 