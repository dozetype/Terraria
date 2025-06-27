#include "Player.h"


void Player::draw() const {
    DrawCircle(pos.x, pos.y, 10, {255,255,255,255});
}
void Player::moveLeft() {
    pos.x -= 1;
}
void Player::moveRight() {
    pos.x += 1;
}
void Player::externalForce(const Vector2 force) {
    pos.x += force.x;
    pos.y += force.y;
}