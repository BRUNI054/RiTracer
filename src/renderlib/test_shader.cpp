#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "lambertian.hpp"
#include "normalShader.hpp"
#include "framebuffer.hpp"
#include "perspectiveCamera.hpp"
#include "blinnPhong.hpp"


int main() {
    framebuffer fb(400, 400);
    perspectiveCamera p(400, 400, 0.250f, 0.250f, 1.0f, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    light l(vec3(10,10,-5));
    scene s = scene(color(0.5f, 0.5f, 0.5f), l);
    s.pushback_shape(std::make_shared<sphere>(vec3(0.0f, 0.0f, -10.0f), 1.0f, std::make_shared<blinnPhong>(10.0f, color(0, 1, 0))));
    // s.pushback_shape(std::make_shared<triangle>(vec3(-1.0f, -1.0f, -20.0f), vec3(1.0f, -1.0f, -20.0f), vec3(0.0f, 1.0f, -20.0f), std::make_shared<blinnPhong>(color(1, 1, 1))));
    for (int x = 0; x < fb.get_width(); x++) {
        for (int y = 0; y < fb.get_height(); y++) {
            ray r;
            p.generateRay(x, y, r);

            color c = s.computeRayColor(r, 1.0, 10000.0);

            fb.setPixelColor(x, y, c);
        }
    }
    fb.exportAsPNG("ShadedSphere.png");

}