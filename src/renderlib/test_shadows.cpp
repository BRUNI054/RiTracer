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
#include <random>

float randomOffset() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

int main() {
    color skyBlue(0.529f, 0.808f, 0.922f);
    color yellow(1.0f, 1.0f, 0.0f);
    color purple(0.75f, 0.4f, 0.75f);
    color forestGreen(0.0f, 0.5f, 0.2f);

    framebuffer fb(800, 800);
    perspectiveCamera p(800, 800, 1.0f, 1.0f, 1.0f, vec3(0.0f, 3.0f, 0.0f), vec3(0.0f, -.1250f, -1.0f));
    light l(vec3(2,6,0),vec3(1,1,1));
    scene s = scene(skyBlue, l);

    // s.pushback_shape(std::make_shared<sphere>(vec3(1.0f, 3.0f, -7.0f), 1.0f, std::make_shared<blinnPhong>(75.0f, yellow, s)));
    // s.pushback_shape(std::make_shared<sphere>(vec3(-1.0f, 1.0f, -10.0f), 1.0f, std::make_shared<blinnPhong>(75.0f, color(0.096f, 0.184f, 0.296f), s)));
    s.pushback_shape(std::make_shared<sphere>(vec3(0.5f, 3.0f, -5.0f), 1.0f, std::make_shared<blinnPhong>(100, forestGreen, std::make_shared<scene>(s))));
    s.pushback_shape(std::make_shared<triangle>(vec3(-3.5f, 0, -10), vec3(-2, 4, -12), vec3(-0.5f, 0, -14), std::make_shared<lambertian>(yellow, std::make_shared<scene>(s))));
    s.pushback_shape(std::make_shared<sphere>(vec3(0.0f, -1000.0f, -10.0f), 1000.0f, std::make_shared<shadeToGreen>(purple, std::make_shared<scene>(s))));

    // s.pushback_shape(std::make_shared<triangle>(vec3(-4, 0, -11), vec3(-2, 4, -12), vec3(0, 0, -13), std::make_shared<lambertian>(yellow, s)));
    // s.pushback_shape(std::make_shared<triangle>(vec3(-1.0f, -1.0f, 20.0f), vec3(0.0f, 1.0f, 20.0f), vec3(1.0f, -1.0f, 20.0f), std::make_shared<blinnPhong>(200.0f, color(0, 1, 0))));

    int nSquare = 1;
    for (int x = 0; x < fb.get_width(); x++) {
        for (int y = 0; y < fb.get_height(); y++) {
            color c = color(0.0f, 0.0f, 0.0f);
            for(int a = 0; a < nSquare; a++) {
                for(int b = 0; b < nSquare; b++) {
                    
                    float aOffset = (float(a)+randomOffset())/float(nSquare);
                    float bOffset = (float(b)+randomOffset())/float(nSquare);

                    ray r;
                    p.generateRay(x+aOffset, y+bOffset, r);

                    c += s.computeRayColor(r, 1.0, 10000.0);
                }
            }
            c = c / float(nSquare*nSquare);
            fb.setPixelColor(x, y, c);
        }
    }
    fb.exportAsPNG("ShadowTest.png");

}