#include <raylib.h>
#include <iostream>

#include "util.h"
#include "titleScreen.h"


class Game {

private:
    ScreenType screenType = TITLE;

    TitleScreen titleScreen {&screenType, 100.0f};

public:
    Game() {

    }

    void update(float dt) {
        switch (screenType) {
        case TITLE:
            titleScreen.update(dt); break;
        default:
            break;
        }
    }

    void draw() {
        switch (screenType) {
        case TITLE:
            titleScreen.draw(); break;
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

    return 0;
}