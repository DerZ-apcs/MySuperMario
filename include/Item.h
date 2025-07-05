#ifndef ITEM_H
#define ITEM_H

#include "../include/Entity.h"

class Item : public Entity {
private:
	float timespan, timespanAcum;
	int point;
	bool appear;
	float bottomAppear;
public:
	Item(int point = 0);

	const int& getPoint() const;
	virtual EntityType getType() const;
	virtual ITEM_TYPE getItemType() const = 0;

	virtual void setAppearBottom(float bottom);
	virtual const float& getAppearBottom();

	virtual void setAppear(bool appear);
	virtual bool isAppear() const;


	virtual void Update() override = 0;
	void draw() override;
	void updateCollision() override;
	void UpdateTexture() override;
	bool isMaxDistance() const;
	void HandleTileCollision(const Tile tile, CollisionType Colltype);
};

#endif