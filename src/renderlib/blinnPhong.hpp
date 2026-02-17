#pragma once

#include "shader.hpp"

class blinnPhong : public shader{
private:
    float p;
    color c;
public:
    blinnPhong(float Phong, color Color) : p(Phong), c(Color) {}
    color rayColor(hitStruct& h, light l) override {
        vec3 lightDirection = (l.getPoint() - h.intersectPoint).get_unit_vector();
        vec3 he = (lightDirection + h.viewDir.get_unit_vector()).get_unit_vector();
        float blinn = std::fmax(0,std::pow((h.normal.dot(he)), p));
        float lamber = std::fmax(0.0, h.normal.dot(lightDirection));
        return c * (lamber + blinn);
    }
};