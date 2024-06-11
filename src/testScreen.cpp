#include "testScreen.h"

TestScreen::TestScreen(ScreenType* screenRef, float worldScale) : Screen(screenRef, worldScale) {
    cameraScale = ((float) GetScreenHeight()) / worldScale;
    mainCamera.target = Vector2{0, 0};
    mainCamera.offset = Vector2{0, 0};
    mainCamera.rotation = 0;
    mainCamera.zoom = cameraScale;
}

void TestScreen::update(float dt) {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_T)) {
        *screenRef = TITLE;
    }
}

void TestScreen::draw() {
    BeginDrawing();
    ClearBackground(colFromHex(0xAAAAAA));
    BeginMode2D(mainCamera);
    {
        uint32_t col = 0x000000;
        for (int i = 10; i > 0; i--) {
            DrawCircle(0, 0, i*10, colFromHex(col));
            col += 0x110000;
        }
    }
    EndMode2D();
    EndDrawing();
}

TestScreen::~TestScreen() {
    
}

