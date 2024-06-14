#include <raylib.h>
#include <util.h>
#include <vector>

class Player {
// all speed should be in units per second (i.e. times delta time) so that times are consistent between frames
    enum Direction { X, Y };

private:
    float gravity;
    float jumpStrength;

    Vector2 position;
    Rectangle hitbox;

    float xSpeed = 0;
    float ySpeed = 0;
    float maxSpeed = 6000.0f;
    float acceleration = 10.0f;
    float deceleration = 1000.0f;
public:
    Player(float gravity, float jumpStrength, Vector2 pos);
    void update(float dt);  // used for other updates, e.g. animation and stuff that just happens
    void updatePosition(float dt, std::vector<Rectangle> colliders);  // used for physics updates and user input
    void draw();

    void inputManager(float dt);

    Vector2 getPosition() { return position; }
    Rectangle getHitbox() { return hitbox; }
    Vector2 getSpeed() { return Vector2 {xSpeed, ySpeed}; }

private:
    
    void decelerate(Direction dir, float dt);
};


