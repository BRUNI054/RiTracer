#pragma once

#include <memory>

class shader;

struct hitStruct {
    int depth;
    float t;
    vec3 normal;
    vec3 intersectPoint;
    vec3 viewDir;
    std::shared_ptr<shader> shade;
};