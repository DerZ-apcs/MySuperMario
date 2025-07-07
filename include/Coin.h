#ifndef COIN_H
#define COIN_H
#include "../include/Item.h"

class GameEngine;

class Coin : public Item {
private:
	float BLOCK_COIN_LIFE_TIME = 0.5f;
	static constexpr int POINT = 100;
	static constexpr float COIN_UP_VELOCITY = 100.f;
	CoinType type;

	float lifeTime;
public:
	Coin(CoinType type = STATIC_COIN, Vector2 position = { 0.f, 0.f });

	~Coin();
	EntityType getEntityType() const override;
	const CoinType& getCoinType() const;
	
	ITEM_TYPE getItemType() const override;

	void Update() override;
	void draw() override;
	//void updateCollision() override;
	void UpdateTexture() override;
};



#endif