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

	void Update() override;
	void draw() override;
	void UpdateTexture() override;

};

#endif // 
