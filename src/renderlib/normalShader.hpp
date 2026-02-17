#pragma once

#include "shader.hpp"

class normalShader : public shader {
private:
public:
    normalShader() {}
    color rayColor(hitStruct& h, light l) override {
        //h.normal << std::cout << '\n';
        color normalColors = h.normal + vec3(1.0f, 1.0f, 1.0f);
        normalColors *= 0.5f;        
        return normalColors;
    }
};