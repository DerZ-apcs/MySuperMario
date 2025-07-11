#include "../include/Star.h"
#include "../include/ResourceManager.h"

Star::Star(Vector2 pos, Vector2 sz, Direction dir) :
	PowerItem(pos, sz, dir, Singleton<ResourceManager>::getInstance().getTexture("STAR")) {
}

void Star::onConsume(Mario& mario) {
	powerUpState = CONSUMED;
	// score
}
