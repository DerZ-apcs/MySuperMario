#ifndef BANZAIBILL_H
#define BANZAIBILL_H

#include "../include/Bullet.h"

class BanzaiBill : public Bullet {
private:
    const float SPEED_BANZAIBILL = 100.f;
public:
	BanzaiBill(Vector2 pos, Texture2D tex);
    BanzaiBill(Vector2 pos, Texture2D texture, Direction direction);
    ~BanzaiBill();
    ENEMY_TYPE getEnemyType() const override;
	void UpdateTexture() override;
    float getScores() const override;
};
#endif