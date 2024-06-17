#pragma once 

#include <raylib.h>
#include <raymath.h>

#include <util.h>


class TitleScreen : Screen {

private:
    float cameraScale;
    Camera2D mainCamera;

    Font font;

    // images
    Texture2D titleTex = LoadTextureFromImage(LoadImage("assets/images/titletext.png"));

public: 
    TitleScreen(ScreenType* screenRef, float worldScale);
    void initialise(Font font);  // set all the things that cannot be constructed immediately
    void update(float dt) override;
    void draw() override;
    ~TitleScreen();

private:
    void drawGrid();  // debug draw
    void drawTitleAndText();

};
