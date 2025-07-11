//#ifndef SHELL_H
//#define SHELL_H
//
//#include "../include/Enemy.h"
//
//class GameEngine;
//class Character;
//
//class Shell :public Enemy {
//private:
//	SHELL_TYPE type;
//
//	bool isKicked;
//	bool isHold;
//	float inShellTime;
//
//	const float IN_SHELL_TIME = 100.f;
//	const float OUT_SHELL_TIME = 3.f;
//	const float SPIN_SPEED = 200.f;
//public:
//	~Shell();
//
//	Shell(SHELL_TYPE type = GREEN_SHELL, Vector2 position = { 0.f, 0.f });
//
//	ENEMY_TYPE getEnemyType() const override;
//
//	void Update() override;
//	void UpdateTexture() override;
//	void draw() override;
//	void setIsHold(bool hold);
//	bool getIsHold() const;
//	void setIsKicked(bool kicked);
//	bool getIsKicked() const;
//	void kicked(Direction direction = RIGHT) override;
//	void stomped(Vector2 center = { 0.f, 0.f });
//	void attacked(Direction direction = RIGHT) override;
//
//	void setHoldingPosition(const Character* character);
//};
//
//#endif