
#include "player.h"

Player::Player(float gravity, float jumpStrength, Vector2 pos) {
    this->gravity = gravity;
    this->jumpStrength = jumpStrength;
    this->position = pos;
    hitbox = RectCentre(pos, 8, 12);
}

void Player::updatePosition(float dt, std::vector<Rectangle> colliders) {

}

void Player::update(float dt) {

}

void Player::draw() {
    DrawRectangleRounded(hitbox, 0, 1, RED);
}
