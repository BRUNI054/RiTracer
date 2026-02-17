#pragma once

#include "vec3.hpp"
#include <cmath>

class polar {
private:
    float radius;
    float angle;
    float axialDistance;
    float pi = acos(-1);
public:
    polar() : radius(1.0f), angle(0.0f), axialDistance(0.0f) {}
    polar(float r, float a, float d) : radius(r), angle(a), axialDistance(d) {}

    float getRadius() {return radius;}
    float getAngle() {return angle;}
    float getAxialDistance() {return axialDistance;}

    vec3 xAxisConversion() {
        return vec3(axialDistance, (radius*sin(angle*pi/180.0f)), -(radius*(cos(angle*pi/180.0f))));
    }
    vec3 yAxisConversion() {
        return vec3((radius*(cos(angle*pi/180.0f))), axialDistance, -(radius*sin(angle*pi/180.0f)));
    }
    vec3 zAxisConversion() {
        return vec3((radius*(cos(angle*pi/180.0f))), (radius*sin(angle*pi/180.0f)), axialDistance);
    }

};