#include "scene.hpp"
#include "shader.hpp"
#include "shape.hpp"
#include "vec3.hpp"
#include "hitStruct.hpp"

void::scene::pushback_shape(std::shared_ptr<shape> s) {
    objects.push_back(s);
}

color::scene::computeRayColor(const ray& r, float tmin, float tmax) {
    hitStruct h = hitStruct();
    float localTmax = tmax;

    bool hitShape = false;
    for (int idx=0; idx<objects.size(); idx++) {
        if (objects[idx]->intersect(r, tmin, localTmax, h )) {
            hitShape = true;
        }
    }

    if (hitShape) {
        std::shared_ptr<shader> shade = h.shade;
        color c = shade->rayColor(h, l, this);
        return c;
    }
    else {
        return bg;
    }
}