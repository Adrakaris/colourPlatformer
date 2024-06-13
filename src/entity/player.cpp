
#include "player.h"

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
    if(IsKeyDown(KEY_W))
    {
        ySpeed -= acceleration;
    }
    if(IsKeyDown(KEY_A))
    {
        xSpeed -= acceleration;
    }
    if(IsKeyDown(KEY_S))
    {
        ySpeed += acceleration;
    }
    if(IsKeyDown(KEY_D))
    {
        xSpeed += acceleration;
    }

    // Deceleration isn't perfect, I use dt to try get it as close to 0 as possible.
    // ToDo:
    if(!(IsKeyDown(KEY_A) || IsKeyDown(KEY_D)))
    {
        if(xSpeed > 0.2f)
        {
            xSpeed -= deceleration * dt;
        }
        else if (xSpeed < -0.2f)
        {
            xSpeed += deceleration * dt;
        }
    }

    xSpeed = Clamp(xSpeed, -maxSpeed, maxSpeed);
    ySpeed = Clamp(ySpeed, -maxSpeed, maxSpeed);

}