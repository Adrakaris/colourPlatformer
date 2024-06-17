#include "titleScreen.h"

TitleScreen::TitleScreen(ScreenType* screenRef, float worldScale) : Screen(screenRef, worldScale) {
    cameraScale = ((float) GetScreenHeight()) / worldScale;
    mainCamera.target = Vector2{0, 0};
    mainCamera.offset = Vector2{GetScreenWidth()/2.0f, 0};
    mainCamera.rotation = 0;
    mainCamera.zoom = cameraScale;
}


void TitleScreen::initialise(Font font) {
    this->font = font;
}


void TitleScreen::update(float dt) {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_T)) {
        *screenRef = TEST;
    }

}



void TitleScreen::draw() {
    BeginDrawing();
    ClearBackground(colFromHex(0xAAAAAA));
    BeginMode2D(mainCamera);
    {
        drawGrid();

        drawTitleAndText();

    }
    EndMode2D();    
    EndDrawing();
}


void TitleScreen::drawTitleAndText() {
    // Rectangle titleBox = DrawTextExCentred(font, "COLOURPLAN", Vector2{0, 10}, 16, 1, BLACK);
    float textureLeft = -titleTex.width/4.0f;
    float topLine = 10;
    DrawTextureEx(titleTex, Vector2{textureLeft, 10}, 0, 0.5f, WHITE);
    // std::cout << "Title Box " << titleBox << std::endl;
    DrawTextEx(font, "A platformer game about colouring", Vector2{textureLeft, topLine + titleTex.height/2.0f -3}, 
               4, 0, BLACK);

}


void TitleScreen::drawGrid() {
    Color gridCol = colFromHexAlpha(0x00770044);

    for (int i = -500; i < 500; i += 10) {
        DrawLine(-1000, i, 1000, i, gridCol);
        DrawTextEx(font, TextFormat("%d", i), Vector2{ 0.3, (float)i }, 3, 0, gridCol);
        if (i % 100 == 0) {
            DrawLine(-1000, i, 1000, i, gridCol);
        }
    }

    for (int j = -500; j < 500; j += 10) {
        DrawLine(j, -1000, j, 1000, gridCol);
        DrawTextEx(font, TextFormat("%d", j), Vector2{ j+0.3f, 0.3 }, 3, 0, gridCol);
        if (j % 100 == 0) {
            DrawLine(j, -1000, j, 1000, gridCol);
        }
    }
}


TitleScreen::~TitleScreen() {
    
}

