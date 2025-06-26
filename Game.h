#ifndef GAME_H
#define GAME_H
#include <raylib.h>
#include <vector>
#include "Block.h"
#include "Player.h"


class Game {
public:
    Game();
    ~Game();

    void update();
    void draw() const;
    void input();
    std::vector<Block> createBlocks();

private:
    Player player;
    std::vector<Block> blocks;
    float gravity;
};



#endif //GAME_H
