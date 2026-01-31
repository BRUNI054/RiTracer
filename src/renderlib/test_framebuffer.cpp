#include "Framebuffer.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <random>

#include "./../png++/png.hpp"

int main() {
    Framebuffer f(200, 200);
    color red(1.0f, 0.0f, 0.0f);
    color green( 0.596f, 1.0f, 0.596f);
    f.clearToColor(red);
    f.exportAsPNG("red_test.png");
    f.clearToHorizontalGradient(red, green);
    f.exportAsPNG("red_green_h_test.png");
    f.clearToVerticalGradient(red, green);
    f.exportAsPNG("red_green_v_test.png");
}