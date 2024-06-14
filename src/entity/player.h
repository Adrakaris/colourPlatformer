#include <raylib.h>
#include <util.h>
#include <vector>
#include <string>

class Player {
// all speed should be in units per second (i.e. times delta time) so that times are consistent between frames
    enum Direction { X, Y };
    enum PlayerState { ON_GROUND, IN_AIR };

private:
    float gravity = 20;
    float jumpStrength = 48*8;

    // Vector2 position;
    Rectangle hitbox;
    Rectangle lastHitbox;

    float xSpeed = 0;
    float ySpeed = 0;
    const float maxSpeed = 480.0f;
    const float acceleration = 15.0f;
    const float deceleration = 3000.0f;

    // bool onGround = false;
    PlayerState state = IN_AIR;
public:
    Player(Vector2 pos);
    void update(float dt);  // used for other updates, e.g. animation and stuff that just happens
    void updatePosition(float dt, std::vector<Rectangle> colliders);  // used for physics updates and user input
    void draw();

    void inputManager(float dt);

    Vector2 getPosition() { return Vector2{hitbox.x + hitbox.width/2, hitbox.y + hitbox.height/2}; }
    Rectangle getHitbox() { return hitbox; }
    Vector2 getSpeed() { return Vector2 {xSpeed, ySpeed}; }

    void setPosition(Vector2 newPos) { hitbox = RectCentre(newPos, hitbox.width, hitbox.height); }
    void resetSpeed() { xSpeed = ySpeed = 0; }

    std::string getStateValue();

private:
    void decelerate(Direction dir, float dt);
    void updateCollisionWithGround(const Rectangle& rect, float dt);
};

