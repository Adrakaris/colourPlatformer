
#include "player.h"
#include <algorithm>

Player::Player(Vector2 pos) {
    // this->position = pos;
    hitbox = RectCentre(pos, 8, 12);
    lastHitbox = hitbox;
}

void Player::updatePosition(float dt, std::vector<Rectangle> colliders) {
    // manual copy?
    lastHitbox.x = hitbox.x;
    lastHitbox.y = hitbox.y;

    if (state == IN_AIR) {
        ySpeed += gravity;
    }

    // position.x += xSpeed * dt;
    // position.y += ySpeed * dt;
    hitbox.x += xSpeed * dt;
    hitbox.y += ySpeed * dt;


    // this is the least efficient method of collision detection but should be fine
    state = IN_AIR;  // TODO: we need some better way of finding state this is kinda dumb
    for (auto rect : colliders) {
        updateCollisionWithGround(rect, dt);
    }
}

void Player::updateCollisionWithGround(const Rectangle& rect, float dt) {
    if (!CheckCollisionRecs(rect, hitbox)) return;
      // we assume if the player has not moved no more collision need to be detected.
    // several cases:
    // -- when bottom of the (last) hitbox is below the collided rect, and we intersect, we have collided from the side
    // -- when top of the (last) hitbox is below the collided rect, we have collided from the bottom
    // -- otherwise if the bottom of the (last) hitbox is above, we collide from above.

    // Vector2 dirFromPrev {
    //     hitbox.x - lastHitbox.x,
    //     hitbox.y - lastHitbox.y
    // };  // movement direction vector

    // std::cout << "COLLISION: Rect " << rect << " hbox " << hitbox << " lasthbox " << lastHitbox << std::endl;

    if (CheckCollisionRecs(rect, lastHitbox)) {
        state = ON_GROUND;
        return;  // we assume if both hitboxes are colliding then we have already struct something and dont need to then check it
    }
    
    if (lastHitbox.y + lastHitbox.height <= rect.y) {  // fall onto a box
        state = ON_GROUND;
        ySpeed = 0;
        hitbox.y = rect.y - hitbox.height;
    } else if (lastHitbox.y >= rect.y + rect.height) {  // jump into a box
        ySpeed = 0;
        hitbox.y = rect.y + rect.height;
    } else if (lastHitbox.x <= rect.x) {  // collide with box from left
        xSpeed = 0;
        hitbox.x = rect.x - hitbox.width;
    } else { // collide with box from right
        xSpeed = 0;
        hitbox.x = rect.x + rect.width;
    }


    // possible edge case:
    // -- moving too fast that we clip through a block. 
    //    solution: check in movement direction a limited distance from the previous hitbox (8 units)

}

void Player::update(float dt) {
    inputManager(dt);
}

void Player::draw() {
    DrawRectangleRounded(lastHitbox, 0, 1, Color{0, 255, 0, 60});
    DrawRectangleRounded(hitbox, 0, 1, RED);
}

void Player::inputManager(float dt) {
    // if (IsKeyDown(KEY_W)) {
    //     ySpeed -= acceleration;
    // }
    if (IsKeyDown(KEY_A)) {
        xSpeed -= acceleration;
    }
    // if (IsKeyDown(KEY_S)) {
    //     ySpeed += acceleration;
    // }
    if (IsKeyDown(KEY_D)) {
        xSpeed += acceleration;
    }
    if (IsKeyDown(KEY_SPACE) && state != IN_AIR) {
        ySpeed -= jumpStrength;  // big boost to jump
    }

    // Deceleration isn't perfect, I use dt to try get it as close to 0 as possible.
    // ToDo:
    decelerate(X, dt);
    // decelerate(Y, dt);

    xSpeed = Clamp(xSpeed, -maxXSpeed, maxXSpeed);
    ySpeed = Clamp(ySpeed, -maxYSpeed, maxYSpeed);
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

std::string Player::getStateValue() {
    switch (state) {
        case ON_GROUND: return "on_ground";    
        case IN_AIR: return "in_air";
        default: return "ERR_STATE_NOT_ACCOUNTED_FOR";
    }
}
