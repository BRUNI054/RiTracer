#pragma once

#include "shader.hpp"

class shadeToGreen : public shader {
private:
    color c_;
    std::shared_ptr<scene> s_;
public:
    shadeToGreen(color c, std::shared_ptr<scene> s) : c_(c), s_(s) {}
    color rayColor(hitStruct& h, light l) override {
        vec3 lightDirection = (l.getPoint() - h.intersectPoint);
        float lamber = std::fmax(0.0, h.normal.dot(lightDirection.get_unit_vector()));
        color temp = color(lamber, 1.0, lamber);
        color finalColor = c_ * temp;
        if(shader::inShadow(h, lightDirection, s_)){
            return finalColor*0.5f;
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