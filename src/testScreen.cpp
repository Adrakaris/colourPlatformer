#include "testScreen.h"
#include <iostream>


void _printMapProperties(TmxProperty properties[], uint32_t pLength);
void _printMapLayers(TmxLayer layers[], uint32_t lLength);

void printMapInformation(TmxMap* p_map) {
    using namespace std;

    printf("Map of %s (orientation %d, width %d, height %d, tile W/H %d/%d)\n", p_map->fileName, p_map->orientation, p_map->width, p_map->height, p_map->tileWidth, p_map->tileHeight);

    cout << "==Map Properties==\n";
    _printMapProperties(p_map->properties, p_map->propertiesLength);

    cout << "==Layers==\n";
    _printMapLayers(p_map->layers, p_map->layersLength);

}

void _printMapProperties(TmxProperty properties[], uint32_t pLength) {
    using namespace std;

    for (uint32_t i = 0; i < pLength; i++) {
        TmxProperty* property = &properties[i];
        cout << i << ") PROPERTY name: " << property->name  << " value: ";
        switch (property->type) {
            case PROPERTY_TYPE_STRING: cout << property->stringValue << endl; break;
            case PROPERTY_TYPE_INT: cout << property->intValue << endl; break;
            case PROPERTY_TYPE_BOOL: cout << property->boolValue << endl; break;
            case PROPERTY_TYPE_FLOAT: cout << property->floatValue << endl; break;
            case PROPERTY_TYPE_FILE: cout << "FILE<" << property->stringValue << ">" << endl; break;
            case PROPERTY_TYPE_OBJECT: cout << "OBJECT<" << property->intValue << ">" << endl; break;
            case PROPERTY_TYPE_COLOR: cout << "COL<###>" << endl; break;
        }
    }
}

void _printMapLayers(TmxLayer layers[], uint32_t lLength) {
    using namespace std;

    for (uint32_t i = 0; i < lLength; i++) {
        TmxLayer* layer = &layers[i];
        cout << "=== Layer\n";
        cout << i << ") name: " << layer->name << " type: ";
        switch (layer->type) {
            case LAYER_TYPE_TILE_LAYER: cout << "TILE\n"; break;
            case LAYER_TYPE_OBJECT_GROUP: cout << "OBJECT\n"; break; 
            case LAYER_TYPE_IMAGE_LAYER: cout <<"IMAGE\n"; break;
            case LAYER_TYPE_GROUP: cout << "GROUP\n";
        }
        cout << "=== Layer properties\n";
        _printMapProperties(layer->properties, layer->propertiesLength);
    }
}


TestScreen::TestScreen(ScreenType* screenRef, float worldScale) : Screen(screenRef, worldScale) {
    cameraScale = ((float) GetScreenHeight()) / worldScale;
    mainCamera.zoom = cameraScale;
    mainCamera.target = cameraTarget;
    mainCamera.offset = Vector2{((float) GetScreenWidth())/2.0f, ((float) GetScreenHeight())/2.0f};
    mainCamera.rotation = 0;

    p_map = LoadTMX("assets/levels/test_level.tmx");
    printMapInformation(p_map);  // debug

    // get colliders
    TmxLayer* collLayer = findTmxObjLayerWithName(p_map, "ground_coll");
    // std::cout << "I found layer " << collLayer->name << std::endl;
    levelColliders = extractAABBsFromObjLayer(collLayer);
    std::cout << "colliders";
    for (auto rect : levelColliders) {
        std::cout << rect << " ";
    }
    std::cout << std::endl;

    // get waypoints
    TmxLayer* waypoints = findTmxObjLayerWithName(p_map, "waypoints");
    waypointObjects = getTmxObjectsNameMap(waypoints);
    for (auto entry : waypointObjects) {
        std::cout << entry.first << ": (x=" << entry.second->x << ", y=" << entry.second->y << ")\n";
    }

    startPoint = getObjPos(waypointObjects.at("player_spawn"));

    // setup player
    player = std::make_unique<Player>(startPoint);
}

void TestScreen::update(float dt) {
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_T)) {
        *screenRef = TITLE;
    }

    if (IsKeyPressed(KEY_P)) {
        pause = !pause;
    }
    // if (pause) return;
    // temporary (allow advancing frame by frame when paused)
    if (!IsKeyPressed(KEY_K) && pause) {
        return;
    }
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_R)) {
        player->setPosition(getObjPos(waypointObjects.at("player_spawn")));
    }


    player->update(dt);
    player->updatePosition(dt, levelColliders);

    timer += dt;
    if (timer > 1) {
        timer = 0;
        std::cout << "(Player) speed: " << player->getSpeed()  
            << " state: " << player->getStateValue() 
            << " pos: " << player->getPosition() 
            << std::endl;
    }

    mainCamera.target = player->getPosition();
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

        player->draw();

        // for (auto rect : levelColliders) {
        //     DrawRectangleRoundedLines(rect, 0, 1, 0.3, GREEN);
        // }
    }
    EndMode2D();
    {
        char data[40];
        sprintf_s<40>(data, "Position: (%.2f, %.2f)", player->getPosition().x, player->getPosition().y);
        DrawText(data, 8, 8, 12, BLACK);
        if (pause) {
            DrawText("PAUSED", 8, 20, 20, RED);
        }
    }
    EndDrawing();
}

TestScreen::~TestScreen() {
    UnloadTMX(p_map);
}

