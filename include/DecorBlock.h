#ifndef DECORBLOCK_H
#define DECORBLOCK_H

#include "Blocks.h"

class DecorBlock : public Blocks {
public:
    DecorBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
    DecorBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }, std::string textureName = "TILE_0");

    void draw() override;
    void Update() override;
    BLOCK_TYPE getBlockType() const override;
};
#endif // !DECORBLOCK_H
