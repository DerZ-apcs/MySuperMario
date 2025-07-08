#ifndef HIDDENBLOCK_H
#define HIDDENBLOCK_H

#include "Blocks.h"

class HiddenBlock : public Blocks {
private:
    bool revealed = false;
public:
    HiddenBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
    HiddenBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }, std::string textureName = "TILE_0");
    BLOCK_TYPE getBlockType() const override;
    void Update() override;
    void UpdateTexture() override;
    void draw() override;
    void reveal();
};
#endif // !HIDDENBLOCK_H
