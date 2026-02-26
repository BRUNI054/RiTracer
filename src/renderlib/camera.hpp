#pragma once

#include "ray.hpp"

class camera {
public:
    camera() : pos(0,0,0), U(1.0f,0,0), V(0,1.0f,0), W(0,0,1.0f), focalLength(1.0f), imageplaneWidth(0.5f), imageplaneHeight(0.5f), nx(100), ny(100) {}

    camera(int pixel_nx, int pixel_ny) : pos(0,0,0), U(1.0f,0,0), V(0,1.0f,0), W(0,0,1.0f), focalLength(1.0f), imageplaneWidth(0.5f), imageplaneHeight(0.5f), nx(pixel_nx), ny(pixel_ny) {}

    camera(int pixel_nx, int pixel_ny, float viewport_height, float viewport_width) : pos(0,0,0), U(1,0,0), V(0,1,0), W(0,0,1), focalLength(1.0f), imageplaneWidth(viewport_width), imageplaneHeight(viewport_height), nx(pixel_nx), ny(pixel_ny) {}

    camera(int pixel_nx, int pixel_ny, float viewport_height, float viewport_width, float focal_length, vec3 origin, vec3 dir) : pos(origin), focalLength(focal_length), imageplaneWidth(viewport_width), imageplaneHeight(viewport_height), nx(pixel_nx), ny(pixel_ny), W(dir.get_unit_vector()) {
        vec3 b(0, 1.0f, 0);
        vec3 temp1 = b.cross(W);
        temp1.get_unit_vector();
        U = temp1;
        V = W.cross(U);
    }

    virtual ~camera() {}

    virtual void generateRay(float i, float j, ray& r) = 0;

protected:
    vec3 pos;
    vec3 U, V, W;
    float focalLength;
    float imageplaneWidth, imageplaneHeight;
    int nx, ny;
};
