
#include <util.h>
#include <raylib.h>


class TestScreen : Screen {

private:
    float cameraScale;
    Camera2D mainCamera;

public: 
    TestScreen(ScreenType* screenRef, float worldScale);
    void update(float dt) override;
    void draw() override;
    ~TestScreen();

};
