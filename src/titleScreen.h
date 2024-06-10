#pragma once 

#include <raylib.h>
#include <raymath.h>

#include "util.h"


class TitleScreen : Screen {

private:
    float cameraScale;
    Camera2D mainCamera;

public: 
    TitleScreen(ScreenType* screenRef, float worldScale);
    void update(float dt) override;
    void draw() override;
    ~TitleScreen();

};
