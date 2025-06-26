#ifndef PLAYER_H
#define PLAYER_H
#include "../../../../../opt/homebrew/Cellar/raylib/5.5/include/raylib.h"


class Player {
public:
    Player();
    ~Player();

    void draw() const;
    void moveLeft();
    void moveRight();
    void moveJump();
    void externalForce(Vector2 force);


private:
    Vector2 pos;
};



#endif //PLAYER_H
