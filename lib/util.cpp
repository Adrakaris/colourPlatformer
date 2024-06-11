#include <string>

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

