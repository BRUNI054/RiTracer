#pragma once

#include "vec3.hpp"
#include "light.hpp"
#include <memory>


class scene;
class hitStruct;

class shader {
protected:
public:
    virtual color rayColor(hitStruct& h, light l) = 0;
    bool inShadow(hitStruct& h, vec3 lightDirection, std::shared_ptr<scene> s_);
    // {
    //     for(auto shape: s.getObjects()) {
    //         hitStruct shadowStruct;
    //         ray shadowRay(h.intersectPoint, h.intersectPoint - l.getPoint());
    //         float tmax = shadowRay.direction().length();
    //         if(shape->intersect(shadowRay, 0, tmax, shadowStruct) = true){
    //             return true;
    //         }
    //     }
    //     return false;
    // }
};
