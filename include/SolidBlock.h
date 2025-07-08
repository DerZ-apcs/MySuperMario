#ifndef SOLIDBLOCK_H
#define SOLIDBLOCK_H

#include "../include/Blocks.h"

class SolidBlock : public Blocks {
public:
    SolidBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    SolidBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }, std::string textureName = "TILE_0");
    BLOCK_TYPE getBlockType() const override;
    void Update() override;
    void draw() override;
    //void UpdateTexture() override;
};
#endif // !SOLIDBLOCK_H
