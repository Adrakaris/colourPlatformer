
#include <util.h>
#include <raylib.h>
#include <raytmx.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include "entity/player.h"



class TestScreen : Screen {

private:
    const float radius = 8;
    
    float cameraScale;
    Camera2D mainCamera;
    Vector2 cameraTarget = {0, 0};

    //

    TmxMap* p_map;

    std::vector<Rectangle> levelColliders = {};
    std::unordered_map<std::string, TmxObject*> waypointObjects;
    TmxTileLayer* tileLayer;

    Vector2 startPoint;

    //

    std::unique_ptr<Player> player;

    float timer = 0;  // this is for printing data at specific intervals

    bool pause = false;

public: 
    TestScreen(ScreenType* screenRef, float worldScale);
    void update(float dt) override;
    void draw() override;
    ~TestScreen();

};
