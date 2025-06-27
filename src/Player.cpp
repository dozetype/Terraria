#include "Player.h"


Player::Player()
    :vel{0, 0},
    pos{static_cast<float>(GetScreenWidth()/2), static_cast<float>(GetScreenHeight()/2)-200}
{

}

Player::~Player() {
}

void Player::draw() const {
    DrawCircle(pos.x, pos.y, 10, {255,255,255,255});
}

void Player::update() {
    //Final Stage of Frame
    pos.x += vel.x;
    pos.y += vel.y;
}

void Player::moveLeft() {
    vel.x -= 3;
}

void Player::moveRight() {
    vel.x += 3;
}

void Player::setYVel(const float num) {
    vel.y = num;
}

void Player::setXVel(const float num) {
    vel.x = num;
}

bool Player::getGrounded() {
    return grounded;
}

void Player::setGrounded(const bool status) {
    grounded = status;
}

Rectangle Player::getRec() const {
    return {pos.x, pos.y, 16, 16};
}
