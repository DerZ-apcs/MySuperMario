#ifndef PIRANHAPLANT_H
#define PIRANHAPLANT_H

#include "../include/Enemy.h"

class PiranhaPlant : public Enemy {
protected:
    float popUpTimer; // Timer để kiểm soát chu kỳ trồi/rút
    bool isPoppingUp; // Trạng thái trồi lên hay rút xuống
    float popUpHeight; // Độ cao tối đa khi trồi lên
    float baseY; // Vị trí Y ban đầu (đáy ống)
    float invincibilityTimer;
    float delayTimer;
    static const float POP_UP_DURATION; // Thời gian trồi lên/rút xuống
    static const float STAY_UP_DURATION; // Thời gian ở trạng thái trồi lên
    static const float DURATION_BETWEEN_POPUP; // rest between two popups
    PIRANHA_TYPE piranhaType;
public:
    PiranhaPlant(Vector2 pos, Texture2D texture);
	virtual PIRANHA_TYPE getPiranhaType() const; // virtual function to get Piranha type
    void Update() override;
    void draw() override;
    void UpdateTexture() override;
    ENEMY_TYPE getEnemyType() const override;
    void stomped() override;
    float getScores() const override;
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};


#endif