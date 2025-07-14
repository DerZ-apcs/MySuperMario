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
	virtual EntityType getEntityType() const;
	virtual ITEM_TYPE getItemType() const = 0;

	virtual void setAppearBottom(float bottom);
	virtual const float& getAppearBottom();

	virtual void setAppear(bool appear);
	virtual bool isAppear() const;


	virtual void Update() override;
	virtual void draw() override;
	virtual void updateCollision() override;
	virtual void UpdateTexture() override;
};

#endif