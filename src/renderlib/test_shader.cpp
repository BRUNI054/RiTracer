#include "scene.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "lambertian.hpp"
#include "normalShader.hpp"
#include "framebuffer.hpp"
#include "perspectiveCamera.hpp"
#include "blinnPhong.hpp"
#include "shadeToGreen.hpp"
#include "blinnPhreak.hpp"


int main() {
    framebuffer fb(200, 200);
    perspectiveCamera p(200, 200, 0.25f, 0.25f, 1.0f, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    light l(vec3(2,2,-6), vec3(1,1,1));
    scene s = scene(color(0.5f, 0.5f, 0.5f), l);
    // s.pushback_shape(std::make_shared<sphere>(vec3(0.0f, 0.0f, -10.0f), 1.0f, std::make_shared<blinnPhong>(75.0f, color(0, 1, 0))));
    s.pushback_shape(std::make_shared<sphere>(vec3(0.0f, 0.0f, -10.0f), 1.0f, std::make_shared<lambertian>(75.0, color(0.096f, 0.184f, 0.296f))));

    // s.pushback_shape(std::make_shared<triangle>(vec3(-1.0f, -1.0f, 20.0f), vec3(0.0f, 1.0f, 20.0f), vec3(1.0f, -1.0f, 20.0f), std::make_shared<blinnPhong>(200.0f, color(0, 1, 0))));
    for (int x = 0; x < fb.get_width(); x++) {
        for (int y = 0; y < fb.get_height(); y++) {
            ray r;
            p.generateRay(x, y, r);

            color c = s.computeRayColor(r, 1.0, 10000.0);

            fb.setPixelColor(x, y, c);
        }
    }
    fb.exportAsPNG("BlinnPhongSphere.png");

}