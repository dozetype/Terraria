#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>
#include "Constants.h"


class Player {
public:
    Player();
    ~Player();
    void draw() const;
    // void externalForce(const Vector2 force);
    void update();
    void moveLeft();
    void moveRight();
    void moveJump();
    void setYVel(float num);
    void setXVel(float num);
    void setXPos(int x);
    void setYPos(int y);
    bool getGrounded();
    void setGrounded(bool status);
    Rectangle getRec() const;
    Vector2 getPos() const;
private:
    Vector2 vel;
    Vector2 pos;
    bool grounded;
};


#endif //PLAYER_H
