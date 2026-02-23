#pragma once

#include "shader.hpp"

class shadeToGreen : public shader {
private:
    color c_;
public:
    shadeToGreen(color c) : c_(c) {}
    color rayColor(hitStruct& h, light l) override {
        vec3 lightDirection = (l.getPoint() - h.intersectPoint).get_unit_vector();
        float lamber = std::fmax(0.0, h.normal.dot(lightDirection));
        color temp = color(lamber, 1.0, lamber);
        return c_ * temp;
    }
};