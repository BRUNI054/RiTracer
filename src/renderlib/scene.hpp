#pragma once

#include <vector>
#include <memory>
#include "vec3.hpp"
#include "shape.hpp"
#include "hitStruct.hpp"

class scene {
private:
    std::vector<std::shared_ptr<shape>> objects;
    color bg;
    light l;
public:
    scene() : bg(color(1.0f, 1.0f, 1.0f)), l(light()) {}
    scene(color background) : bg(background), l(light()) {}
    scene(color background, light light) : bg(background), l(light) {}

    void pushback_shape(std::shared_ptr<shape> s) {
        objects.push_back(s);
    }

    color computeRayColor(const ray& r, float tmin, float tmax) {
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
            color c = shade->rayColor(h, l);
            return c;
        }
        else {
            return bg;
        }
    }


};