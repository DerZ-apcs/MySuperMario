#ifndef COIN_BLOCK_H
#define COIN_BLOCK_H

#include <raylib.h>
#include "../include/Blocks.h" 
#include "../include/Coin.h"
#include "../include/TextEffect.h"
#include "../include/CoinEffect.h"

class CoinBlock : public Blocks {
private:
	bool isActive = true;
	int coinCount;

public:
	CoinBlock(Vector2 pos, Vector2 size);
	~CoinBlock() = default;

	bool getActive() const;
	void setActive(bool active);
	void setCount(int count);
	void Activate();

	BLOCK_TYPE getBlockType() const override;

	void draw() override;
	void loadEntity(const json& j) override;
	void saveEntity(json& j) const override;
};

#endif // !COIN_BLOCK_H