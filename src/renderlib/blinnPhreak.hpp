#pragma once

#include "shader.hpp"

class blinnPhreak : public shader{
private:
    float p;
    color c;
public:
    blinnPhreak(float Phong, color Color) : p(Phong), c(Color) {}
    color rayColor(hitStruct& h, light l) override {
        vec3 lightDirection = (l.getPoint() - h.intersectPoint);
        vec3 he = (lightDirection - h.viewDir).get_unit_vector();
        float blinn = std::pow(std::fmax(0.0f, (h.normal.dot(he))), p);
        float lamber = std::fmax(0.0f, h.normal.dot(lightDirection.get_unit_vector()));
        color lambSauce = c*lamber;
        color blinnp = (l.getColor()*blinn) - (lambSauce);
        if (blinnp.x() < 0) {
            blinnp.set_x(0.0f);
        }
        if (blinnp.y() < 0) {
            blinnp.set_y(0.0f);
        }
        if (blinnp.z() < 0) {
            blinnp.set_z(0.0f);
        }
        color temp = blinnp + lambSauce;
        return temp;
    }
};