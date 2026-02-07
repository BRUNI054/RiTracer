#pragma once

#include "camera.hpp"

class perspectiveCamera : public camera {
public:
    perspectiveCamera() : camera() {}
    perspectiveCamera(int pixel_nx, int pixel_ny) : camera(pixel_nx, pixel_ny) {}
    perspectiveCamera(int pixel_nx, int pixel_ny, float viewport_height, float viewport_width, float focal_length, vec3 origin, vec3 dir) : camera(pixel_nx, pixel_ny, viewport_height, viewport_width, focal_length, origin, dir) {}

    void generateRay(int i, int j, ray& r) override {
        float u, v, l, ri, b, t;
        l = -imageplaneWidth/2.0;
        ri = imageplaneWidth/2.0;
        t = imageplaneHeight/2.0;
        b = -imageplaneHeight/2.0;
        u = l+((ri-l)*(i+0.5)/float(nx));
        v = b+((t-b)*(j+0.5)/float(ny));
        ray temp = ray(r.origin(), (-W*focalLength) + (U*u) + (V*v));
        r = temp;
    }
};