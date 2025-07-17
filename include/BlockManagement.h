#ifndef BLOCKMANAGEMENT_H
#define BlOCKMANAGEMENT_h
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

// Use the factory design pattern

class BlockManagement {
public:
	using BlockCreator = std::function<Blocks* (Vector2, Vector2)>;
	static BlockManagement& getInstance() {
		static BlockManagement instance;
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
	
	BlockManagement() = default;
	~BlockManagement() = default;
	BlockManagement(const BlockManagement&) = delete;
	BlockManagement& operator=(const BlockManagement&) = delete;
};

// Block creation functions

//Blocks* createFloor(Vector2 pos, Vector2 size) { return new Floor(pos, size); }
Blocks* createBrick(Vector2 pos, Vector2 size) { return new Brick(pos, size); }
//Blocks* createSolidBlock(Vector2 pos, Vector2 size) { return new SolidBlock(pos, size); }
//Blocks* createMovingBlock(Vector2 pos, Vector2 size) { return new MovingBlock(pos, size); }
Blocks* createItemBlock(Vector2 pos, Vector2 size) { return new ItemBlock(pos, size); }
//Blocks* createHiddenBlock(Vector2 pos, Vector2 size) { return new HiddenBlock(pos, size); }
//Blocks* createDecorBlock(Vector2 pos, Vector2 size) { return new DecorBlock(pos, size); }
//Blocks* createTempBlock(Vector2 pos, Vector2 size) { return new TemporaryBlock(pos, size); }


// register all blocks types

inline void registerBlocks() {
	BlockManagement& factory = BlockManagement::getInstance();

	//factory.registerBlock(FLOOR, createFloor);
	factory.registerBlock(BRICK, createBrick);
	//factory.registerBlock(SOLIDBLOCK, createSolidBlock);
	//factory.registerBlock(MOVINGBLOCK, createMovingBlock);
	factory.registerBlock(ITEMBLOCK, createItemBlock);
	//factory.registerBlock(HIDDEN, createHiddenBlock);
	//factory.registerBlock(DECOR, createDecorBlock);
	//factory.registerBlock(TEMPBLOCK, createTempBlock);
}

#endif