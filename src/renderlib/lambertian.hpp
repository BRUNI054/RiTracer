#pragma once

#include "shader.hpp"
#include "light.hpp"
#include <iostream>

class lambertian : public shader {
private:
    color c_;
public:
    lambertian(color c) : c_(c) {}
    color rayColor(hitStruct& h, light l) override {
        vec3 lightDirection = (l.getPoint() - h.intersectPoint).get_unit_vector();
        float lamber = std::fmax(0.0, h.normal.dot(lightDirection));
        return c_ * lamber;
    }
};