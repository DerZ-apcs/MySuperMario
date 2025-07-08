#ifndef ITEMBLOCK_H
#define ITEMBLOCK_H

#include "Blocks.h"

class Character;
class Fireball;
class Entity;

class ItemBlock : public Blocks {
private:
    bool hasItem = true;
    ITEM_TYPE item; // item inside
    int subType;
    bool isBouncing = false;
    float bounceTime = 0.0f;
    const float bounceHeight = 8.0f;
    const float bounceDuration = 0.2f;
    float OgY;
public:
    ItemBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
    ItemBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }, std::string textureName = "TILE_0");
    BLOCK_TYPE getBlockType() const override;
    void draw() override;
    void Update() override;
    void UpdateTexture() override;
    void releaseItem(const Entity* object);
    void setItem(ITEM_TYPE item, int subtype);
};

#endif // !ITEMBLOCK_H
