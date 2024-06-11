#include "testScreen.h"

TestScreen::TestScreen(ScreenType* screenRef, float worldScale) : Screen(screenRef, worldScale) {
    cameraScale = ((float) GetScreenHeight()) / worldScale;
    mainCamera.target = cameraTarget;
    mainCamera.offset = Vector2{((float) GetScreenWidth())/2.0f, ((float) GetScreenHeight())/2.0f};
    mainCamera.rotation = 0;
    mainCamera.zoom = cameraScale;

    p_map = LoadTMX("assets/levels/test_level.tmx");

}

void TestScreen::update(float dt) {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_T)) {
        *screenRef = TITLE;
    }

    if (IsKeyDown(KEY_RIGHT)) {
        cameraTarget.x += 1;
    }
    if (IsKeyDown(KEY_LEFT)) {
        cameraTarget.x -= 1;
    }
    if (IsKeyDown(KEY_UP)) {
        cameraTarget.y -= 1;
    }
    if (IsKeyDown(KEY_DOWN)) {
        cameraTarget.y += 1;
    }
    mainCamera.target = cameraTarget;
}

void TestScreen::draw() {
    BeginDrawing();
    ClearBackground(colFromHex(0xAAAAAA));
    BeginMode2D(mainCamera);
    {
        uint32_t col = 0x00000000;
        for (int i = 10; i > 0; i--) {
            DrawCircle(0, 0, i*10, colFromHexAlpha(col));
            col += 0x11000011;
        }

        // draw tilemap
        AnimateTMX(p_map);
        DrawTMX(p_map, &mainCamera, 0, 0, WHITE);
    }
    EndMode2D();

    
    EndDrawing();
}

TestScreen::~TestScreen() {
    UnloadTMX(p_map);
}

