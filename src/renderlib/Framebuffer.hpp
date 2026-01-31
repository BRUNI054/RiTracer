#pragma once

#include <vector>
#include "vec3.hpp"

class Framebuffer{
public:
    Framebuffer();

    Framebuffer(int w, int h);

    void clearToColor(color c);

    void clearToVerticalGradient(color top, color bottom);

    void clearToHorizontalGradient(color left, color right);

    void setPixelColor(int x, int y, color c);

    void exportAsPNG(std::string filename);

private:
    int width, height;
    std::vector<color> fbStorage;
};