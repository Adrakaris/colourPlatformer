#pragma once 

#include <raylib.h>
#include <raymath.h>
#include <cstdint>
#include <raytmx.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>


namespace consts {
    const float epsilon = 0.0001f;
}



// screen definitoins
enum ScreenType {
    TITLE, TEST
};

// screen class
class Screen {
protected:
    float worldScale;  // world coordinate scale -- how many camera units are from top to bottom
    ScreenType* screenRef;  // this isnt very OOP but ... ah whatever

public:
    Screen(ScreenType* screenRef, float worldScale) {
        this->screenRef = screenRef;
        this->worldScale = worldScale;
    };
    virtual void update(float dt) = 0;  // pure virutal function -- a function which MUST be overridden
    virtual void draw() = 0;
};

// text util functions

// draw text centre-justified on the left-right -- the top-bottom is not centred!
inline void DrawCentredText(const Font& font, const char* text, Vector2 position, float fontSize, float fontSpacing, Color tint) {
    Vector2 bbox = MeasureTextEx(font, text, fontSize, fontSpacing);
    position.x -= bbox.x / 2;  // centre the text by moving the position halfway left
    DrawTextEx(font, text, position, fontSize, fontSpacing, tint);
}


// raytmx util functions

TmxLayer* findTmxObjLayerWithName(const TmxMap* map_ref, const char* name);  // can return null
TmxLayer* findTmxTiledLayerWithName(const TmxMap* map_ref, const char* name);
std::vector<Rectangle> extractAABBsFromObjLayer(const TmxLayer* objLayerRef);
std::unordered_map<std::string, TmxObject*> getTmxObjectsNameMap(const TmxLayer* objLayerRef); // expects all objects to have unique names!
inline Vector2 getObjPos(const TmxObject* objectRef) { return Vector2 {(float)objectRef->x, (float)objectRef->y}; }

// colour util functions
#pragma region colour_util_functions

// convert RGB (A = 255)
constexpr Color colFromHex(std::uint32_t hexCode) {
    // assuming input of the form #(00)RRGGBB rather than #RRGGBBAA
    unsigned char red = (unsigned char)((hexCode >> 16) & 0xFF);
    unsigned char green = (unsigned char)((hexCode >> 8) & 0xFF);
    unsigned char blue = (unsigned char)((hexCode) >> 0);
    return Color {red, green, blue, 255};
}

// convert RGBA
constexpr Color colFromHexAlpha(std::uint32_t hexCode) {
    unsigned char red = (unsigned char)((hexCode >> 24) & 0xFF);
    unsigned char green = (unsigned char)((hexCode >> 16) & 0xFF);
    unsigned char blue = (unsigned char)((hexCode >> 8) & 0xFF);
    unsigned char alpha = (unsigned char)(hexCode);
    return Color {red, green, blue, alpha};
}

// color definitions

#pragma endregion


#pragma region Shape and TExt


inline Rectangle RectCentre(Vector2 centre, float width, float height) {
    return Rectangle{
        centre.x - width/2.0f,
        centre.y - height/2.0f,
        width, height
    };
}

// element wise multiplies an array of vector of points by scale
inline void scaleShape(Vector2* points, int numPoints, float scale) {
    for (int i = 0; i < numPoints; i++) {
        // std::cout << "Prev shape " << points[i].x << "," << points[i].y << "; ";
        points[i] = Vector2Scale(points[i], scale);
        // std::cout << "New shape " << points[i].x << "," << points[i].y << "; " << std::endl;
    }
}

// draw text centre-justified on the left-right -- the top-bottom is not centred! Returns the bounding box
inline Rectangle DrawTextExCentred(const Font& font, const char* text, Vector2 position, float fontSize, float fontSpacing, Color tint) {
    Vector2 bbox = MeasureTextEx(font, text, fontSize, fontSpacing);
    position.x -= bbox.x / 2;  // centre the text by moving the position halfway left
    DrawTextEx(font, text, position, fontSize, fontSpacing, tint);
    return Rectangle { position.x, position.y, bbox.x, bbox.y };
}



#pragma endregion

// struct print overloads
std::ostream& operator<<(std::ostream& os, const Rectangle& rect);

inline std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
    return os << "(" << vec.x << ", " << vec.y << ")";
}

inline bool operator==(Rectangle r1, Rectangle r2) {
    return r1.x == r2.x && r1.y == r2.y && r1.height == r2.height && r1.width == r2.width;
}

