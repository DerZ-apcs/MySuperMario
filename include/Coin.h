#ifndef COIN_H
#define COIN_H
#include <raylib.h>
#include "../include/Tile.h"
#include "../include/Item.h"

class GameEngine;

class Coin : public Item {
private:
	static constexpr int POINT = 100;
	CoinType coinType;

public:
	Coin(CoinType type, Vector2 pos);
	~Coin() = default;

	EntityType getEntityType() const override;
	const CoinType& getCoinType() const;
	ITEM_TYPE getItemType() const override;
	const int& getPoint() const;

	void Update() override;
	void draw() override;
	void UpdateTexture() override;

};

#endif // COIN_H
