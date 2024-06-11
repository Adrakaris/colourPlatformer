
#include <util.h>
#include <raylib.h>
#include <raytmx.h>
#include <vector>



class TestScreen : Screen {

private:
    float cameraScale;
    Camera2D mainCamera;
    Vector2 cameraTarget = {0, 0};

    TmxMap* p_map;

    std::vector<Rectangle> levelColliders = {};

public: 
    TestScreen(ScreenType* screenRef, float worldScale);
    void update(float dt) override;
    void draw() override;
    ~TestScreen();

};
