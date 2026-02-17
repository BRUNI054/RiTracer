#pragma once

#include <vector>
#include "vec3.hpp"

class framebuffer{
private:
    int width, height;
    std::vector<color> fbStorage;
public:
    framebuffer();

    framebuffer(int w, int h);

    void clearToColor(color c);

    void clearToVerticalGradient(color top, color bottom);

    void clearToHorizontalGradient(color left, color right);

    void setPixelColor(int x, int y, color c);

    void exportAsPNG(std::string filename);

    int get_width() {return width;}

    int get_height() {return height;}

};