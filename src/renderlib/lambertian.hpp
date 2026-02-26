#pragma once

#include "shader.hpp"
#include "light.hpp"
#include <iostream>

class lambertian : public shader {
private:
    color c_;
    std::shared_ptr<scene> s_;
public:
    lambertian(color c, std::shared_ptr<scene> s) : c_(c), s_(s) {}
    color rayColor(hitStruct& h, light l) override {
        vec3 lightDirection = (l.getPoint() - h.intersectPoint);
        float lamber = std::fmax(0.0, h.normal.dot(lightDirection.get_unit_vector()));
        color finalColor = c_*lamber;
        if(shader::inShadow(h, lightDirection, s_)){
            return finalColor*0.0F;
        }
        return finalColor;
    }
    // bool inShadow(hitStruct& h, vec3 lightDirection) {
    //     hitStruct shadowStruct;
    //     ray shadowRay(h.intersectPoint, (lightDirection));
    //     float tmax = lightDirection.length();
    //     for (int idx=0; idx<s_.getObjects().size(); idx++) {
    //         if (s_.getObjects()[idx]->intersect(shadowRay, 0, tmax, shadowStruct)) {
    //             return true;
    //         }
    //     }
    //     return false;
    // }
};