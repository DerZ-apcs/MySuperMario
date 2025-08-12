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

    BLOCK_TYPE getBlockType() const override;
    void Update() override;
    void setDying(bool dying);
    void draw() override;
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};
#endif // !TEMPORARYBLOCK_H
