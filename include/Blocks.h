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
private:
    int id = 0;

public:
    Blocks(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
    Blocks(Vector2 pos, Vector2 size, std::string textureName);
    virtual ~Blocks() = default;

    void setId(int id);
	int getId() const;
    EntityType getEntityType() const override;
    virtual BLOCK_TYPE getBlockType() const = 0;
    virtual void Update() override;
    virtual void draw() override;
    virtual void UpdateTexture() override;
};
#endif