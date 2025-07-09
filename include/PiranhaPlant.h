//#ifndef PIRANHAPLANT_H
//#define PIRANHAPLANT_H
//
//#include "../include/Enemy.h"
//
//class PiranhaPlant : public Enemy {
//protected:
//    float popUpTimer; // Timer để kiểm soát chu kỳ trồi/rút
//    bool isPoppingUp; // Trạng thái trồi lên hay rút xuống
//    float popUpHeight; // Độ cao tối đa khi trồi lên
//    float baseY; // Vị trí Y ban đầu (đáy ống)
//    float invincibilityTimer;
//    Mario& mario;
//    float delayTimer;
//    static const float POP_UP_DURATION; // Thời gian trồi lên/rút xuống
//    static const float STAY_UP_DURATION; // Thời gian ở trạng thái trồi lên
//public:
//    PiranhaPlant(Vector2 pos, Texture2D texture, Mario& mario);
//    void Update() override;
//    void draw() override;
//    void UpdateTexture() override;
//    void CollisionWithCharacter(Mario& mario, CollisionType collType) override;
//    void CollisionWithEnemy(Enemy& enemy, CollisionType collType) override;
//    void HandleTileCollision(const Tile& tile, CollisionType collType) override;
//};
//
//
//#endif