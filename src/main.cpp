#include <raylib.h>
#include <iostream>

#include <util.h>
#include "titleScreen.h"
#include "testScreen.h"

#define RAYTMX_IMPLEMENTATION
#include <raytmx.h>

class Game {

private:
    ScreenType screenType = TEST;

    TitleScreen titleScreen {&screenType, 100.0f};
    TestScreen testScreen {&screenType, 8.0f * 24};

public:
    Game() {

    }

    void update(float dt) {
        switch (screenType) {
        case TITLE:
            titleScreen.update(dt); break;
        case TEST:
            testScreen.update(dt);
        default:
            break;
        }
    }

    void draw() {
        switch (screenType) {
        case TITLE:
            titleScreen.draw(); break;
        case TEST:
            testScreen.draw();
        default:
            break;
        }
    }

    ~Game() {

    }

};



int main()
{
    std::cout << "CPP VERSION:" << __cplusplus << std::endl;

    InitWindow(1440, 960, "Colour Platformer");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose()) {
        game.update(GetFrameTime());
        game.draw();

    }
    CloseWindow();
    return 0;
}