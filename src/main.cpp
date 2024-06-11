#include <raylib.h>
#include <iostream>

#include <util.h>
#include "titleScreen.h"
#include "testScreen.h"

#define RAYTMX_IMPLEMENTATION
#include <raytmx.h>

class Game {

private:
    ScreenType screenType = TITLE;

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

    // const char* tmx = "assets/levels/test_level.tmx";
    // TmxMap* map = LoadTMX(tmx);

    // Camera2D camera;
    // camera.zoom = 1.0f;
    // camera.target.x = (float)(map->width * map->tileWidth) / 2.0f;
    // camera.target.y = (float)(map->height * map->tileHeight) / 2.0f;
    // camera.offset.x = (float)1440 / 2.0f;
    // camera.offset.y = (float)960 / 2.0f;
    // camera.rotation = 0.0f;

    while (!WindowShouldClose()) {
        game.update(GetFrameTime());
        game.draw();

        // Draw the tilemap
        // BeginDrawing();
        // {
        //     ClearBackground(BLACK);
        //     BeginMode2D(camera);
        //     {
        //         AnimateTMX(map);
        //         DrawTMX(map, &camera, 100, 100, WHITE);
        //     }
        //     EndMode2D();
        //     DrawFPS(10, 10);
        // }
        // EndDrawing();
    }
    // UnloadTMX(map);
    CloseWindow();
    return 0;
}