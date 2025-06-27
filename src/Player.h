#ifndef PLAYER_H
#define PLAYER_H
#include <raylib.h>


class Player {
public:
    void draw() const;
    void moveLeft();
    void moveRight();
    void externalForce(const Vector2 force);
private:
    Vector2 pos = {static_cast<float>(GetScreenWidth()/2), static_cast<float>(GetScreenHeight()/2)};
};


#endif //PLAYER_H
