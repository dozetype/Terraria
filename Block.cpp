#include "Block.h"

Block::Block(const Vector2 pos): pos(pos) {}

Block::~Block() {
}

void Block::draw(const Texture2D& texture) const {
    DrawTextureV(texture, pos, WHITE);
}
