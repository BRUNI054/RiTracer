#pragma once

#include "vec3.hpp"

class light {
private:
    point pos;
    color c;
public:
    light() : pos(point(0.0f, 0.0f, 0.0f)), c(color(1.0f, 1.0f, 1.0f)) {}
    light(point position) : pos(position), c(color(1.0f, 1.0f, 1.0f)) {}
    point getPoint() {return pos;}
    color getColor() {return c;}
};