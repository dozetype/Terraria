#include "Player.h"

Player::Player() {
    pos = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
}

Player::~Player() {
}

void Player::draw() const {
    DrawCircle(pos.x, pos.y, 30, {255,255,255,255});
}

void Player::moveLeft() {
    pos.x -= 3;
}

void Player::moveRight() {
    pos.x += 3;
}

void Player::moveJump() {

}

void Player::externalForce(const Vector2 force) {
    pos.x += force.x;
    pos.y += force.y;
}



