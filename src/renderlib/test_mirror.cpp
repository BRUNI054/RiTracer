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
#include "mirror.hpp"
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
    perspectiveCamera p(800, 800, 1.0f, 1.0f, 1.0f, vec3(0.0f, 4.0f, 0.0f), vec3(0.0f, -0.125f, -1.0f));
    light l(vec3(3,5,0),vec3(1,1,1));
    std::shared_ptr<scene> s = std::make_shared<scene>(skyBlue, l);

    // s->pushback_shape(std::make_shared<sphere>(vec3(1.0f, 3.0f, -7.0f), 1.0f, std::make_shared<blinnPhong>(75.0f, yellow, s)));
    // s->pushback_shape(std::make_shared<sphere>(vec3(-1.0f, 1.0f, -10.0f), 1.0f, std::make_shared<blinnPhong>(75.0f, color(0.096f, 0.184f, 0.296f), s)));
    s->pushback_shape(std::make_shared<sphere>(vec3(0.5f, 2.0f, -7.50f), 0.5f, std::make_shared<lambertian>(forestGreen, s)));
    s->pushback_shape(std::make_shared<sphere>(vec3(2.0f, 2.0f, -8.0f), 1.0f, std::make_shared<mirror>(s)));
    s->pushback_shape(std::make_shared<sphere>(vec3(0.0f, -10000.0f, 0.0f), 10000.0f, std::make_shared<lambertian>(purple, s)));
    s->pushback_shape(std::make_shared<sphere>(vec3(-2.0f, 2.0f, -8.0f), 2.0f, std::make_shared<mirror>(s)));
    
    // s->pushback_shape(std::make_shared<triangle>(vec3(-2.0f, 0, -7), vec3(0, 3.46, -9), vec3(2, 0, -7), std::make_shared<lambertian>(yellow, s)));
    // s->pushback_shape(std::make_shared<triangle>(vec3(-2.0f, 0, -11), vec3(0, 3.46, -9), vec3(2, 0, -11), std::make_shared<lambertian>(yellow, s)));
    // s->pushback_shape(std::make_shared<triangle>(vec3(-2.0f, 0, -7), vec3(0, 3.46, -9), vec3(-2, 0, -11), std::make_shared<lambertian>(yellow, s)));
    // s->pushback_shape(std::make_shared<triangle>(vec3(2.0f, 0, -7), vec3(0, 3.46, -9), vec3(2, 0, -11), std::make_shared<lambertian>(yellow, s)));
    // s->pushback_shape(std::make_shared<triangle>(vec3(-10, 0, 0), vec3(0, 100, -20), vec3(0, 0, -20), std::make_shared<mirror>(s)));
    // s->pushback_shape(std::make_shared<triangle>(vec3(0.0, 0, -20), vec3(0, 100, -20), vec3(10, 0, 0), std::make_shared<mirror>(s)));
    // s->pushback_shape(std::make_shared<triangle>(vec3(-10, 0, 0), vec3(0, 0, -20), vec3(10, 0, 0), std::make_shared<lambertian>(yellow*0.8, s)));
    
    // s->pushback_shape(std::make_shared<triangle>(vec3(-4, 0, -11), vec3(-2, 4, -12), vec3(0, 0, -13), std::make_shared<lambertian>(yellow, s)));
    // s->pushback_shape(std::make_shared<triangle>(vec3(-1.0f, -1.0f, 20.0f), vec3(0.0f, 1.0f, 20.0f), vec3(1.0f, -1.0f, 20.0f), std::make_shared<blinnPhong>(200.0f, color(0, 1, 0))));

    int nSquare = 4;
    for (int x = 0; x < fb.get_width(); x++) {
        for (int y = 0; y < fb.get_height(); y++) {
            color c = color(0.0f, 0.0f, 0.0f);
            for(int a = 0; a < nSquare; a++) {
                for(int b = 0; b < nSquare; b++) {
                    
                    float aOffset = (float(a)+randomOffset())/float(nSquare);
                    float bOffset = (float(b)+randomOffset())/float(nSquare);

                    ray r;
                    p.generateRay(x+aOffset, y+bOffset, r);

                    c += s->computeRayColor(r, 1.0, std::numeric_limits<float>::infinity(), 8);
                }
            }
            c = c / float(nSquare*nSquare);
            fb.setPixelColor(x, y, c);
        }
    }
    fb.exportAsPNG("MirrorTest.png");

}