#ifndef COIN_H
#define COIN_H
#include <raylib.h>
#include "../include/Tile.h"
#include "../include/Entity.h"

class Coin : public Entity {
private:
	bool isCollected = false;

public:
	Coin(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, float timeSpan);
	~Coin() = default;
	
	bool getCollected() const;
	void setCollected(bool collected);

	EntityType getEntityType() const override;
	const CoinType& getCoinType() const;

	const int& getPoint() const {
		return 100;
	} // to be destroyed after merge

	void Update() override;
	void draw() override;
	void UpdateTexture() override;

};

#endif // COIN_H
