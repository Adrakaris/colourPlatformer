#include <raylib.h>
#include <util.h>
#include <vector>

class Player {
// all speed should be in units per second (i.e. times delta time) so that times are consistent between frames
private:
    float gravity;
    float jumpStrength;
    Vector2 position;
    Rectangle hitbox;
    float xSpeed = 0;
    float ySpeed = 0;

public:
    Player(float gravity, float jumpStrength, Vector2 pos);
    void update(float dt);  // used for other updates, e.g. animation and stuff that just happens
    void updatePosition(float dt, std::vector<Rectangle> colliders);  // used for physics updates and user input
    void draw();

    Vector2 getPosition() { return position; }
    Rectangle getHitbox() { return hitbox; }
};


