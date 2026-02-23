#pragma once

#include "shader.hpp"
#include "lambertian.hpp"

class blinnPhong : public shader{
private:
    float p;
    color c;
public:
    blinnPhong(float Phong, color Color) : p(Phong), c(Color) {}
    color rayColor(hitStruct& h, light l) override {
        lambertian lamb(c);
        vec3 lightDirection = (l.getPoint() - h.intersectPoint);
        vec3 he = (lightDirection - h.viewDir).get_unit_vector();
        color blinn = (l.getColor()*std::pow(std::fmax(0.0f, (h.normal.dot(he))), p));
        return blinn + lamb.rayColor(h, l);
    }
};