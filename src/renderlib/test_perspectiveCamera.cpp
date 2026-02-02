#include "Framebuffer.hpp"
#include "perspectiveCamera.hpp"


void testCamera(int width, int height) {
    Framebuffer fb(width, height);

    perspectiveCamera p = perspectiveCamera(width, height);

    for (int x=0; x<width; x++) {
        for(int y=0; y<height; y++) {
            ray r;
            p.generateRay(x, y, r);

            color rayDirColor = r.direction();
            rayDirColor = rayDirColor.get_unit_vector();
            rayDirColor += vec3(1.0f,1.0f,1.0f);
            rayDirColor *= 0.5f;
            fb.setPixelColor(x, y, rayDirColor);
        }
    }
    fb.exportAsPNG("defaultCamYRayColors.png");
}

int main() {
    testCamera(800, 800);
    return 0;
}