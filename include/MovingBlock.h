#ifndef MOVINGBLOCK_H
#define MOVINGBLOCK_H

#include "../include/Blocks.h"

class MovingBlock : public Blocks {
private:
    Vector2 velocity = { 50.0f, 50.0f };
    float boundLeft, boundRight;
    float boundTop, boundBottom;

public:
    MovingBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
    //MovingBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 }, std::string textureName = "TILE_0");
    BLOCK_TYPE getBlockType() const override;
    void draw() override;
    void setBounds(float left, float right, float top, float bottom);
    Vector2 getVelocity() const;
    void setVelocity(Vector2 newVelocity);
    void Update() override;
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};
#endif // !MOVINGBLOCK_H
