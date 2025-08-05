#include "../include/Peach.h"
#include "../include/Character.h"

#include <iostream>

Peach::Peach() : 
	Peach(Vector2{ 32, 400 }, Vector2{ 26, 46 }, STATE_SMALL) {
	std::cout << "Peach is created" << std::endl;
	characterType = PEACH;

}

Peach::Peach(Vector2 nposition, Vector2 nsize, CharacterState type) :
	Character(nposition, nsize, type, PEACH)
{
	std::cout << "Peach size after Character constructor: " << size.x << ", " << size.y << std::endl;
}

Peach::~Peach()
{
	std::cout << "Peach is destroyed" << std::endl;
}

CharacterType Peach::getCharacterType() const
{
	return PEACH;
}

void Peach::draw() {
	Character::draw();
}
void Peach::reset() {
	Character::reset();
}

//void Peach::updateCollision()
//{
//	if (isducking) {
//		CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y + size.y / 2 - CollNorth.getHeight() });
//		CollEast.setSize({ 5, size.y / 2 });
//		CollEast.setPos({ position.x + size.x - CollEast.getWidth() , position.y + size.y * 3 / 4 - CollEast.getHeight() / 2 });
//		CollWest.setSize({ 5, size.y / 2 });
//		CollWest.setPos({ position.x , position.y + size.y * 3 / 4 - CollWest.getHeight() / 2 });
//	}
//	else {
//		CollWest.setSize({ 5, size.y - 5 });
//		CollEast.setSize({ 5, size.y - 5 });
//		if ((getCharacterType() == PEACH && getCharacterState() != STATE_SMALL && getCharacterState() != STATE_STAR)) {
//			CollNorth.setPos({ position.x + size.x / 2 - CollNorth.getWidth() / 2, position.y });
//
//			CollSouth.setX(position.x + size.x / 2 - CollSouth.getWidth() / 2);
//			CollSouth.setY(position.y + size.y - CollSouth.getHeight());
//
//			CollEast.setX(position.x + size.x - CollEast.getWidth() - 5);
//			CollEast.setY(position.y + size.y / 2 - CollEast.getHeight() / 2);
//
//			CollWest.setX(position.x + 5);
//			CollWest.setY(position.y + size.y / 2 - CollWest.getHeight() / 2);
//		}
//		else Entity::updateCollision();
//	}
//
//	cout << size.x << " " << size.y << endl;
//}
