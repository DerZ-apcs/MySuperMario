#ifndef ITEM_H
#define ITEM_H

#include "../include/Entity.h"

class Item : public Entity {
private:
	int point;
public:
	Item(int point = 0);
	Item(Vector2 pos, Vector2 sz, Vector2 vel, Direction dir, EntityState state, Texture2D tex);
	const int& getPoint() const;
	virtual EntityType getEntityType() const;
	virtual ITEM_TYPE getItemType() const = 0;

	virtual void Update() override;
	virtual void draw() override;
	virtual void updateCollision() override;
	virtual void UpdateTexture() override;
};

#endif