#include "Player.h"


void Player::draw() const {
    DrawCircle(pos.x, pos.y, 30, {255,255,255,255});
}
void Player::moveLeft() {
    pos.x -= 3;
}
void Player::moveRight() {
    pos.x += 3;
}
void Player::externalForce(const Vector2 force) {
    pos.x += force.x;
    pos.y += force.y;
}