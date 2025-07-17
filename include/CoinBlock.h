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
	CoinBlock(Vector2 pos, std::string tex, int count);
	~CoinBlock() = default;

	bool getActive() const;
	void setActive(bool active);
	void Activate();

	BLOCK_TYPE getBlockType() const override;

	void draw() override;
};

#endif // !COIN_BLOCK_H