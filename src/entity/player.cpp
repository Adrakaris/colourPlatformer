
#include "player.h"
#include <algorithm>

Player::Player(float gravity, float jumpStrength, Vector2 pos) {
    this->gravity = gravity;
    this->jumpStrength = jumpStrength;
    this->position = pos;
    hitbox = RectCentre(pos, 8, 12);
}

void Player::updatePosition(float dt, std::vector<Rectangle> colliders) {
    position.x += xSpeed * dt;
    position.y += ySpeed * dt;
}

void Player::update(float dt) {
    inputManager(dt);
}

void Player::draw() {
    hitbox = RectCentre(position, 8, 12);
    DrawRectangleRounded(hitbox, 0, 1, RED);
}

void Player::inputManager(float dt) {
    if (IsKeyDown(KEY_W)) {
        ySpeed -= acceleration;
    }
    if (IsKeyDown(KEY_A)) {
        xSpeed -= acceleration;
    }
    if (IsKeyDown(KEY_S)) {
        ySpeed += acceleration;
    }
    if (IsKeyDown(KEY_D)) {
        xSpeed += acceleration;
    }

    // Deceleration isn't perfect, I use dt to try get it as close to 0 as possible.
    // ToDo:
    decelerate(X, dt);
    decelerate(Y, dt);

    xSpeed = Clamp(xSpeed, -maxSpeed, maxSpeed);
    ySpeed = Clamp(ySpeed, -maxSpeed, maxSpeed);
}

void Player::decelerate(Direction dir, float dt) {
    bool cond;
    float* speedRef;

    if (dir == X) {
        cond = !(IsKeyDown(KEY_A) || IsKeyDown(KEY_D));
        speedRef = &xSpeed;
    } else {
        cond = !(IsKeyDown(KEY_S) || IsKeyDown(KEY_W));
        speedRef = &ySpeed;
    }

    if (!cond) return;

    if (*speedRef > 5) {
        *speedRef = std::max(*speedRef - deceleration * dt, 0.0f);
    } else if (*speedRef < -5) {
        *speedRef = std::min(*speedRef + deceleration * dt, 0.0f);
    } else {
        *speedRef = 0;
    }
}
