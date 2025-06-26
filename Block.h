#ifndef BLOCK_H
#define BLOCK_H
#include <raylib.h>


class Block {
public:
    Block(Vector2 pos);
    ~Block();

    void draw(const Texture2D &texture) const;

private:
    Vector2 pos;
};

#endif //BLOCK_H
