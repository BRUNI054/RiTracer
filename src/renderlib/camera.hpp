#pragma once

#include "ray.hpp"

class camera {
    public:
    camera() : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1), focalLength(1.0f), imageplaneWidth(0.25), imageplaneHeight(0.25), nx(100), ny(100) {}

    camera(int pixel_nx, int pixel_ny) : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1), focalLength(1.0f), imageplaneWidth(0.25), imageplaneHeight(0.25), nx(pixel_nx), ny(pixel_ny) {}

    camera(int pixel_nx, int pixel_ny, float viewport_height, float viewport_width) : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1), focalLength(1.0f), imageplaneWidth(viewport_width), imageplaneHeight(viewport_height), nx(pixel_nx), ny(pixel_ny) {}



    virtual ~camera() {}

    virtual void generateRay(int i, int j, ray& r) = 0;

    protected:
    vec3 pos;
    vec3 U, V, W;
    float focalLength;
    float imageplaneWidth, imageplaneHeight;
    int nx, ny;
};
