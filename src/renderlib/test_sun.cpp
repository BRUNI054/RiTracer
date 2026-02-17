#include "sphere.hpp"
#include "triangle.hpp"
#include "framebuffer.hpp"
#include "perspectiveCamera.hpp"
#include "polar.hpp"
#include "scene.hpp"
#include "normalShader.hpp"
#include "lambertian.hpp"
#include <memory>
#include <vector>




int main() {
    framebuffer fb(400, 400);
    perspectiveCamera p(400, 400, 0.250f, 0.250f, 1.0f, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
    light l(vec3(5,5,-5));
    color skyBlue(0.529f, 0.808f, 0.922f);
    color yellow(1.0f, 1.0f, 0.0f);
    color orange(1.0f, 0.75f, 0.0f);
    scene s = scene(skyBlue, l);

    float tris = 16.0f;
    for (int i = 0; i < tris; i++) {
        polar point1 (1.80f, ((360.0f/tris)*float(i)-(360.0f/(4*tris))), 20.0f);
        polar point2 (1.80f, ((360.0f/tris)*float(i+1)+(360.0f/(4*tris))), 20.0f);
        polar point3 (2.5f, ((360.0f/tris)*(float(i)+(0.5f))), 20.0f);
        s.pushback_shape(std::make_shared<triangle>(point1.zAxisConversion(), point2.zAxisConversion(), point3.zAxisConversion(), std::make_shared<lambertian>(yellow)));
    }
    s.pushback_shape(std::make_shared<sphere>(point(0.0f, 0.0f, -20.0f), 1.80f, std::make_shared<lambertian>(yellow)));
    // s.pushback_shape(std::make_shared<triangle>(vec3(-0.7, -0.2, 10.0), vec3(0.1, -0.2, 10.0), vec3(-0.3, 0.2, 10.0), std::make_shared<lambertian>(color(0.0, 0.0, 0.0))));
    // s.pushback_shape(std::make_shared<triangle>(vec3(0.7, -0.2, 10.0), vec3(-0.1, -0.2, 10.0), vec3(0.3, 0.2, 10.0), std::make_shared<lambertian>(color(0.0, 0.0, 0.0))));
    // s.pushback_shape(std::make_shared<triangle>(vec3(0.5, 0.3, 10.0), vec3(0.0, 0.3, 10.0), vec3(0.25, 0.6, 10.0), std::make_shared<lambertian>(color(1.0, 1.0, 1.0))));
    // s.pushback_shape(std::make_shared<triangle>(vec3(0.0, 0.3, 10.0), vec3(-0.5, 0.3, 10.0), vec3(-0.25, 0.6, 10.0), std::make_shared<lambertian>(color(1.0, 1.0, 1.0))));
    // s.pushback_shape(std::make_shared<triangle>(vec3(0.25, 0.6, 10.0), vec3(-0.25, 0.6, 10.0), vec3(0.0, 0.3, 10.0), std::make_shared<lambertian>(color(1.0, 1.0, 1.0))));

    for (int x = 0; x < fb.get_width(); x++) {
        for (int y = 0; y < fb.get_height(); y++) {
            ray r;
            p.generateRay(x, y, r);

            color c = s.computeRayColor(r, 1.0, 10000.0);

            fb.setPixelColor(x, y, c);
        }
    }
    fb.exportAsPNG("ShadedSun.png");
}