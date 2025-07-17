#ifndef ITEMBLOCK_H
#define ITEMBLOCK_H

#include "Blocks.h"
 // question block
class Character;
class Fireball;
class Entity;

class ItemBlock : public Blocks {
private:
    bool hasItem = true;
    bool isActive;
    ITEM_TYPE item; // item inside
    //int subType;
    bool isBouncing = false;
    float bounceTime = 0.0f;
    const float bounceHeight = 8.0f;
    const float bounceDuration = 0.2f;
    float OgY;
public:
    ItemBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
    ItemBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }, std::string textureName = "", ITEM_TYPE item = COIN);
    BLOCK_TYPE getBlockType() const override;
    void draw() override;
    void Update() override;
    void UpdateTexture() override;
    void releaseItem(const Entity* object);
    void setItem(ITEM_TYPE item, int subtype);
    bool getActive() const;
    void setActive(bool active);

};

#endif // !ITEMBLOCK_H
