
#include <util.h>
#include <raylib.h>

#include <raytmx.h>


class TestScreen : Screen {

private:
    float cameraScale;
    Camera2D mainCamera;
    Vector2 cameraTarget = {0, 0};

    TmxMap* p_map;

public: 
    TestScreen(ScreenType* screenRef, float worldScale);
    void update(float dt) override;
    void draw() override;
    ~TestScreen();

};
