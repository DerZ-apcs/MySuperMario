#ifndef TEMPORARYBLOCK_H
#define TEMPORARYBLOCK_H

#include "Blocks.h"

class TemporaryBlock : public Blocks {
private:
    float lifeTime;
    bool isDying;
    bool dead;

public:
    TemporaryBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
    TemporaryBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }, std::string textureName = "TILE_0");

    BLOCK_TYPE getBlockType() const override;
    void Update() override;
    void draw() override;
};
#endif // !TEMPORARYBLOCK_H
