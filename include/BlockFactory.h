#ifndef BLOCKFACTORY_H
#define BLOCKFACTORY_H

#include <unordered_map>
#include <functional>
#include "../include/Blocks.h"
#include "../include/Floor.h"
#include "../include/ItemBlock.h"
#include "../include/MovingBlock.h"
#include "../include/Brick.h"
#include "../include/SolidBlock.h"
#include "../include/HiddenBlock.h"
#include "../include/TemporaryBlock.h"
#include "../include/DecorBlock.h"
#include "../include/CloudBlock.h"
#include "../include/NoteBlock.h"
#include "../include/CoinBlock.h"
#include "../include/RotatingBlock.h"
#include "../include/Cannon.h"

// Use the factory design pattern

class BlockFactory {
public:
	using BlockCreator = std::function<Blocks* (Vector2, Vector2)>;
	static BlockFactory& getInstance() {
		static BlockFactory instance;
		return instance;
	}
	
	void registerBlock(BLOCK_TYPE type, BlockCreator creator) {
		creators[type] = creator;
	}
	Blocks* createBlock(BLOCK_TYPE type, Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }) {
		auto it = creators.find(type);
		if (it != creators.end()) {
			return it->second(pos, size);
		}
		return nullptr;
	}
private:
	std::unordered_map<BLOCK_TYPE, BlockCreator> creators;
	
	BlockFactory() = default;
	~BlockFactory() = default;
	BlockFactory(const BlockFactory&) = delete;
	BlockFactory& operator=(const BlockFactory&) = delete;
};

// register all blocks types

inline void registerBlocks() {
	BlockFactory& factory = BlockFactory::getInstance();

	factory.registerBlock(FLOOR, [](Vector2 pos, Vector2 size) {
		return new Floor(pos, size);
		});

	factory.registerBlock(BRICK, [](Vector2 pos, Vector2 size) {
		return new Brick(pos);
		});

	factory.registerBlock(SOLIDBLOCK, [](Vector2 pos, Vector2 size) {
		return new SolidBlock(pos, size);
		});

	factory.registerBlock(MOVINGBLOCK, [](Vector2 pos, Vector2 size) {
		return new MovingBlock(pos, size);
		});
	factory.registerBlock(HIDDEN, [](Vector2 pos, Vector2 size) {
		return new HiddenBlock(pos, size);
		});
	factory.registerBlock(TEMPBLOCK, [](Vector2 pos, Vector2 size) {
		return new TemporaryBlock(pos, size);
		});
	factory.registerBlock(ITEMBLOCK, [](Vector2 pos, Vector2 size) {
		return new ItemBlock(pos, size);
		});

	factory.registerBlock(CANNON, [](Vector2 pos, Vector2 size) {
		return new Cannon(pos);
		});

	factory.registerBlock(DECOR, [](Vector2 pos, Vector2 size) {
		return new DecorBlock(pos, size);
		});
	
	factory.registerBlock(NOTEBLOCK, [](Vector2 pos, Vector2 size) {
		return new NoteBlock(pos);
		});
	
	factory.registerBlock(CLOUDBLOCK, [](Vector2 pos, Vector2 size) {
		return new CloudBlock(pos);
		});
	
	factory.registerBlock(COINBLOCK, [](Vector2 pos, Vector2 size) {
		return new CoinBlock(pos, size);
		});
	
	factory.registerBlock(ROTATINGBLOCK, [](Vector2 pos, Vector2 size) {
		return new RotatingBlock(pos);
		});
}
#endif