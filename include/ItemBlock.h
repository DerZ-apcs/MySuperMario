#ifndef ITEMBLOCK_H
#define ITEMBLOCK_H

#include "Blocks.h"
 // question block
class Character;
class Fireball;
class Entity;

class ItemBlock : public Blocks {
private:
    bool isActive;
    ITEM_TYPE heldPowerUp;
    int subType;// for sub type of mushroom, star 
public:
    ItemBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
    ItemBlock(Vector2 pos = { 0, 0 }, ITEM_TYPE type = MUSHROOM, int subType = 0);
    ~ItemBlock() = default;
    BLOCK_TYPE getBlockType() const override;
    void draw() override;
    void Update() override;
    void UpdateTexture() override;

    bool getActive() const;
    void setActive(bool active);
    void Activate();

};

#endif // !ITEMBLOCK_H
