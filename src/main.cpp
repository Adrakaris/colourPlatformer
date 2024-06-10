#include <raylib.h>
#include <iostream>

#include "util.h"


class Game {

private:
    ScreenType screenType = TITLE;

public:
    Game() {

    }

    void update(float dt) {

    }

    void draw() {

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