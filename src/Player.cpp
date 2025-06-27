#include "Player.h"


Player::Player()
    :vel{0, 0},
    pos{static_cast<float>(GetScreenWidth()/2), static_cast<float>(GetScreenHeight()/2)-200}
{

}

Player::~Player() {
}

void Player::draw() const {
    DrawRectangle(pos.x, pos.y, 10, 10, {255,255,255,255});
}

void Player::update() {
    //Final Stage of Frame
    pos.x += vel.x;
    pos.y += vel.y;
}

void Player::moveLeft() { vel.x -= 3; }

void Player::moveRight() { vel.x += 3; }

void Player::moveJump() { vel.y -= 20; }

void Player::setYVel(const float num) { vel.y = num; }

void Player::setXVel(const float num) { vel.x = num; }

void Player::setXPos(const int x) { pos.x = x; }

void Player::setYPos(const int y) { pos.y = y; }

bool Player::getGrounded() { return grounded; }

void Player::setGrounded(const bool status) { grounded = status; }

Rectangle Player::getRec() const { return {pos.x, pos.y, 16, 16}; }

Vector2 Player::getPos() const { return pos; }
