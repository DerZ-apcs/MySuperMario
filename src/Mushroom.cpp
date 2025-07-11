#include "../include/Mushroom.h"
#include "../include/ResourceManager.h"

Mushroom::Mushroom(Vector2 pos, Vector2 sz, Direction dir) :
	PowerItem(pos, sz, dir, Singleton<ResourceManager>::getInstance().getTexture("MUSHROOM")) {}

void Mushroom::onConsume(Mario& mario) {
	powerUpState = CONSUMED;
	//mario.TransitionToSuper();
}
