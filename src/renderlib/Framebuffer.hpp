#pragma once

#include <vector>


#include "vec3.hpp"

class Framebuffer{
  public:
    Framebuffer();

    Framebuffer(int w, int h);

    void clearToColor(color c);

    void setPixelColor (int i, int j, color);

    void exportAsPNG(std::string filename);

  private:
    int width, height;
    std::vector<color> fbStorage;
};