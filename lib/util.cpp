
#include "util.h"

std::ostream& operator<<(std::ostream& os, const Rectangle& rect) {
    return os << "Rect(x=" << rect.x << ", y=" << rect.y << ", w=" << rect.width << ", h=" << rect.height << ")";
}


TmxLayer* findTmxObjLayerWithName(const TmxMap* map_ref, const char* name) {
    for (uint32_t i = 0; i < map_ref->layersLength; i++) {
        TmxLayer* layer = &map_ref->layers[i];

        if (layer->type != LAYER_TYPE_OBJECT_GROUP) continue;

        if (std::string(layer->name).compare(std::string(name)) == 0) {
            return layer;
        }
    }
    return nullptr;
}

TmxLayer* findTmxTiledLayerWithName(const TmxMap* map_ref, const char* name) {
        for (uint32_t i = 0; i < map_ref->layersLength; i++) {
        TmxLayer* layer = &map_ref->layers[i];

        if (layer->type != LAYER_TYPE_TILE_LAYER) continue;

        if (std::string(layer->name).compare(std::string(name)) == 0) {
            return layer;
        }
    }
    return nullptr;
}

std::vector<Rectangle> extractAABBsFromObjLayer(const TmxLayer* objLayerRef) {
    TmxObject* objects = objLayerRef->exact.objectGroup.objects;
    unsigned int length = objLayerRef->exact.objectGroup.objectsLength;

    std::vector<Rectangle> bbs(length);
    for (unsigned int i = 0; i < length; i++) {
        TmxObject* obj = &objects[i];
        bbs[i] = obj->aabb;
    }
    return bbs;
}


std::unordered_map<std::string, TmxObject*> getTmxObjectsNameMap(const TmxLayer* objLayerRef) {
    TmxObject* objects = objLayerRef->exact.objectGroup.objects;
    unsigned int length = objLayerRef->exact.objectGroup.objectsLength;

    std::unordered_map<std::string, TmxObject*> mapping;
    for (unsigned int i = 0; i < length; i++) {
        std::string name = objects[i].name;
        mapping[objects[i].name] = &objects[i];
    }
    return mapping;
}

