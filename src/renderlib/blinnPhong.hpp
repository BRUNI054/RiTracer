#pragma once

#include "shader.hpp"
#include "lambertian.hpp"

class blinnPhong : public shader{
private:
    float p;
    color c;
    std::shared_ptr<scene> s_;
public:
    blinnPhong(float Phong, color Color, std::shared_ptr<scene> Scene) : p(Phong), c(Color), s_(Scene) {}
    color rayColor(hitStruct& h, light l) override {
        vec3 lightDirection = (l.getPoint() - h.intersectPoint);
        float lamber = std::fmax(0.0, h.normal.dot(lightDirection.get_unit_vector()));
        color finalColor = c*lamber;
        vec3 he = (lightDirection - h.viewDir).get_unit_vector();
        color blinn = (l.getColor()*std::pow(std::fmax(0.0f, (h.normal.dot(he))), p));
        finalColor += blinn;
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