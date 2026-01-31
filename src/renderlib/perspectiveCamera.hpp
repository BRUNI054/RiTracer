#pragma once

#include "camera.hpp"

class perspectiveCamera : public camera {
    public:
    perspectiveCamera() : camera() {}

    void generateRay(int i, int j, ray& r) override {
        float u, v;
        u = imageplaneWidth/i;
        v = imageplaneHeight/j;
        ray temp = ray(r.origin(), -W*focalLength + u*U + v*V);
        r = temp;
    }
};