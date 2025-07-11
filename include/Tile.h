#ifndef TILE_H
#define TILE_H
#include "../include/ResourceManager.h"
#include "../include/Entity.h"
enum TileType {
    TILE_TYPE_NORMAL,
    TILE_TYPE_RIGHT_EDGE,
    TILE_TYPE_LEFT_EDGE
};
class Tile: public Entity {
private:
    TileType tileType;
public:
    Tile(Vector2 pos, TileType type, std::string name);
    void draw() override;
    EntityType getEntityType() const override;
};
#endif