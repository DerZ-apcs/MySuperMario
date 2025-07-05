#ifndef FIREPIRANHAPLANT_H
#define FIREPIRANHAPLANT_H

#include "../include/PiranhaPlant.h"
#include "../include/EnemyFireBall.h"
#include <list>

class FirePiranhaPlant : public PiranhaPlant {
private:
    float fireBallTimer; // Timer để bắn fireball
    static const float FIREBALL_INTERVAL; // Khoảng thời gian giữa các lần bắn
    std::list<EnemyFireBall*> fireballs; // Danh sách fireball
public:
    FirePiranhaPlant(Vector2 pos, Texture2D texture, Mario& mario);
    ~FirePiranhaPlant();
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    void ShootFireBall(); // Bắn fireball
    std::list<EnemyFireBall*>* getFireBalls(); // Lấy danh sách fireball
};

#endif