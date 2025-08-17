#ifndef HIDDENBLOCK_H
#define HIDDENBLOCK_H

#include "Blocks.h"

class HiddenBlock : public Blocks {
private:
    bool revealed = false;
	BLOCK_TYPE revealType = ITEMBLOCK;
public:
    HiddenBlock(Vector2 pos = { 0, 0 }, Vector2 size = { 32, 32 });
	void setRevealType(BLOCK_TYPE type) { revealType = type; }
    BLOCK_TYPE getBlockType() const override;
    void draw() override;
    void reveal();
	bool isrevealed() const { return revealed; }
    void loadEntity(const json& j) override;
    void saveEntity(json& j) const override;
};
#endif // !HIDDENBLOCK_H
