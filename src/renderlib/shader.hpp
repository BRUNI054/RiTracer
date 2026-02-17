#pragma once

#include "hitStruct.hpp"
#include "vec3.hpp"
#include "light.hpp"

class shader {
public:
    virtual color rayColor(hitStruct& h, light l) = 0;
};