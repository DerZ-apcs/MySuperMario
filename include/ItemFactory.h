#pragma once
#include "../include/Item.h"
#include "../include/Coin.h"
#include "../include/Mushroom.h"
#include "../include/Flower.h"
#include "../include/Star.h"
#include <functional>
#include <unordered_map>

class ItemFactory {
public:
	using ItemCreator = std::function<Item* (Vector2, Direction, int)>;

	static ItemFactory& getInstance() {
		static ItemFactory instance;
		return instance;
	}

	void registerItem(ITEM_TYPE type, ItemCreator creator) {
		creators[type] = creator;
	}
private:
	std::unordered_map<ITEM_TYPE, ItemCreator> creators;
	ItemFactory() = default;
	~ItemFactory() = default;
	ItemFactory(const ItemFactory&) = delete;
	ItemFactory& operator=(const ItemFactory&) = delete;
};

inline void registerItems() {
	ItemFactory& factory = ItemFactory::getInstance();

	factory.registerItem(COIN, [](Vector2 pos, Direction direction, int subtype) {
		return new Coin(static_cast<CoinType>(subtype), pos);
		});

	factory.registerItem(MUSHROOM, [](Vector2 pos, Direction direction, int subtype) {
		return new Mushroom(static_cast<MushroomType>(subtype), pos, direction);
		});

	factory.registerItem(FLOWER, [](Vector2 pos, Direction direction, int subtype) {
		return new Flower(static_cast<FlowerType>(subtype), pos, direction);
		});

	factory.registerItem(STAR, [](Vector2 pos, Direction direction, int subtype) {
		return new Star(static_cast<StarType>(subtype), pos, direction);
		});
}