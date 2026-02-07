#include "Framebuffer.hpp"
#include "perspectiveCamera.hpp"
#include <iostream>


void testCamera(int nx, int ny, float width, float height, float foc, vec3 orig, vec3 dir) {
    Framebuffer fb(nx, ny);

    perspectiveCamera p = perspectiveCamera(nx, ny, height, width, foc, orig, dir);
    // perspectiveCamera p;

    for (int x=0; x<nx; x++) {
        for(int y=0; y<ny; y++) {
            ray r;
            p.generateRay(x, y, r);

            color rayDirColor = r.direction();
            rayDirColor = rayDirColor.get_unit_vector();
            rayDirColor += vec3(1.0f,1.0f,1.0f);
            rayDirColor *= 0.5f;
            fb.setPixelColor(x, y, rayDirColor);
        }
    }
    fb.exportAsPNG("AwesomeCameraDebugImage.png");
}

int main() {
    int pix_height = 200;
    int pix_width = 200;
    float height = 0.5f;
    float width = 0.5f;
    float focalLength = 0.0625f;
    vec3 orig(14.0f,15.0f,16.0f);
    vec3 dir(42.0f, 14.3f, 18.6f);
    testCamera(pix_width, pix_height, width, height, focalLength, orig, dir);
    return 0;
}