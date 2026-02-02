#pragma once

#include "camera.hpp"

class perspectiveCamera : public camera {
    public:
    perspectiveCamera() : camera() {}
    perspectiveCamera(int pixel_nx, int pixel_ny) : camera(pixel_nx, pixel_ny) {}

    void generateRay(int i, int j, ray& r) override {
        float u, v, l, ri, b, t;
        l = imageplaneWidth/2;
        ri = -imageplaneWidth/2;
        t = imageplaneHeight/2;
        b = -imageplaneHeight/2;
        u = l+(ri-l)*(i+0.5)/nx;
        v = b+(t-b)*(j+0.5)/ny;
        ray temp = ray(r.origin(), -W*focalLength + u*U + v*V);
        r = temp;
    }
};