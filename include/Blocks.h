#ifndef BLOCKS_H
#define BLOCKS_H
#include <raylib.h>
#include "../include/Entity.h"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>

class Blocks : public Entity {
public:
    Blocks(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 });
    virtual ~Blocks();

    EntityType getType() const;
    virtual BLOCK_TYPE getBlockType() const = 0;
    virtual void Update() override;
    virtual void draw() override;
    virtual void UpdateTexture() override;
protected:
    float timeSpan;
    float timeSpanAcum;
};
#endif