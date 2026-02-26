#pragma once

#include "shader.hpp"

class normalShader : public shader {
private:
    std::shared_ptr<scene> s_;
public:
    normalShader(std::shared_ptr<scene> s) : s_(s) {}
    color rayColor(hitStruct& h, light l) override {
        color normalColors = h.normal + vec3(1.0f, 1.0f, 1.0f);
        normalColors *= 0.5f;
        vec3 lightDirection = l.getPoint() - h.intersectPoint;
        if (shader::inShadow(h, lightDirection, s_)) {
            return normalColors*0.5f;
        }
        return normalColors;
    }
    // bool inShadow(hitStruct& h, light l) {
    //     vec3 lightDirection = l.getPoint()-h.intersectPoint;
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