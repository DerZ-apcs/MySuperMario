#ifndef FIREPIRANHAPLANT_H
#define FIREPIRANHAPLANT_H

#include "../include/PiranhaPlant.h"
#include "../include/EnemyFireBall.h"
#include <list>

class FirePiranhaPlant : public PiranhaPlant {
private:
    float fireBallTimer; // Timer để bắn fireball
    static const float FIREBALL_INTERVAL; // Khoảng thời gian giữa các lần bắn
protected:
    static const int MAX_FIREBALLS = 50;
    std::list<EnemyFireBall*> fireballs; // Danh sách fireball
public:
    FirePiranhaPlant(Vector2 pos, Texture2D texture, Mario& mario);
    ~FirePiranhaPlant();
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    virtual void ShootFireBall(); // Bắn fireball
    std::list<EnemyFireBall*>* getFireBalls(); // Lấy danh sách fireball
};

class RapidFirePiranha : public FirePiranhaPlant {
private:
    static const float FIREBALL_INTERVAL; // Bắn nhanh hơn
    float fireBallTimer;
public:
    RapidFirePiranha(Vector2 pos, Texture2D texture, Mario& mario);
    void Update() override;
    void ShootFireBall() override; // Ghi đè để bắn một fireball
};

class HomingFirePiranha : public FirePiranhaPlant {
private:
    static const float FIREBALL_INTERVAL; // Bắn nhanh hơn
    static const float DETECTION_RANGE; // Phạm vi phát hiện Mario
    float fireBallTimer;
public:
    HomingFirePiranha(Vector2 pos, Texture2D texture, Mario& mario);
	void Update() override;
    void ShootFireBall() override; 
};

#endif