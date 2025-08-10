// BuzzyBeetle.h
#ifndef BUZZYBEETLE_H
#define BUZZYBEETLE_H

#include "../include/Koopa.h"  
#include "../include/FireBall.h"

enum BuzzyBeetleState {
	NORMAL_BUZZY,
	SHELL_BUZZY
};
const float SCORE_STOMP_BUZZY = 100.f;
class BuzzyBeetle : public Koopa {
private:
	BuzzyBeetleState BuzzyState = NORMAL_BUZZY; // Default state is NORMAL_BUZZY
	static const float BUZZY_SHELL_SPEED; // Speed when in shell state
	static const float BUZZY_WALK_SPEED; // Speed when walking normally
	static const float BUZZY_JUMP_SPEED; // Speed when jumping
	static const float BUZZY_SHELL_FRAME_TIME; // Frame time for shell animation
public:
    BuzzyBeetle(Vector2 pos, Texture2D texture);
    void UpdateTexture() override;
	void Update() override;
	void stomped() override;
	void kicked(Direction direction) override;
	void setBuzzyBeetleState(BuzzyBeetleState newState) { BuzzyState = newState; }
	BuzzyBeetleState getBuzzyBeetleState() const { return BuzzyState; }
	float getScores() const override { return SCORE_STOMP_BUZZY; }
	ENEMY_TYPE getEnemyType() const override;
	void loadEntity(const json& j) override;
	void saveEntity(json& j) const override;
};

#endif // BUZZYBEETLE_H