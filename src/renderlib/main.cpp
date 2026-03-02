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

int main(int argc, char* argv[]) {
    int width, height, samples, depth;
    const char* output = "default";

    if (argc >= 2) {
        width = std::atoi(argv[1]);
        height = std::atoi(argv[2]);
    } else {
        width = 200;
        height = 200;
    }
    if (argc >= 3) {
        samples = std::atoi(argv[3]);
    } else {
        samples = 2;
    }
    if (argc >= 4) {
        depth = std::atoi(argv[4]);
    } else {
        depth = 4;
    }
    if (argc >= 5) {
        output = argv[5];
    }

    color skyBlue(0.529f, 0.808f, 0.922f);
    color yellow(1.0f, 1.0f, 0.0f);
    color purple(0.75f, 0.4f, 0.75f);
    color forestGreen(0.0f, 0.5f, 0.2f);

    framebuffer fb(width, height);
    perspectiveCamera p(width, height, 1.0f, 1.0f, 1.0f, vec3(0.0f, 4.0f, 0.0f), vec3(0.0f, -0.125f, -1.0f));
    light l(vec3(3,5,-2),vec3(1,1,1));
    std::shared_ptr<scene> s = std::make_shared<scene>(skyBlue, l);

    
    s->pushback_shape(std::make_shared<triangle>(vec3(-2.0f, 0, -7), vec3(0, 3.46, -9), vec3(2, 0, -7), std::make_shared<lambertian>(yellow, s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(-2.0f, 0, -11), vec3(0, 3.46, -9), vec3(2, 0, -11), std::make_shared<lambertian>(yellow, s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(-2.0f, 0, -7), vec3(0, 3.46, -9), vec3(-2, 0, -11), std::make_shared<lambertian>(yellow, s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(2.0f, 0, -7), vec3(0, 3.46, -9), vec3(2, 0, -11), std::make_shared<lambertian>(yellow, s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(-10, 0, 0), vec3(0, 100, -20), vec3(0, 0, -20), std::make_shared<mirror>(s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(0.0, 0, -20), vec3(0, 100, -20), vec3(10, 0, 0), std::make_shared<mirror>(s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(-10, 100, 0), vec3(0, 100, -20), vec3(-10, 0, 0), std::make_shared<mirror>(s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(10, 0, 0), vec3(0, 100, -20), vec3(10, 100, 0), std::make_shared<mirror>(s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(-10, 100, 0), vec3(10, 0, 0), vec3(-10, 0, 0), std::make_shared<mirror>(s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(10, 100, 0), vec3(-10, 100, 0), vec3(10, 0, 0), std::make_shared<mirror>(s)));
    s->pushback_shape(std::make_shared<triangle>(vec3(-10, 0, 0), vec3(0, 0, -20), vec3(10, 0, 0), std::make_shared<lambertian>(yellow*0.8, s)));
    
    int nSquare = samples;
    for (int x = 0; x < fb.get_width(); x++) {
        for (int y = 0; y < fb.get_height(); y++) {
            color c = color(0.0f, 0.0f, 0.0f);
            for(int a = 0; a < nSquare; a++) {
                for(int b = 0; b < nSquare; b++) {
                    
                    float aOffset = (float(a)+randomOffset())/float(nSquare);
                    float bOffset = (float(b)+randomOffset())/float(nSquare);

                    ray r;
                    p.generateRay(x+aOffset, y+bOffset, r);

                    c += s->computeRayColor(r, 1.0, std::numeric_limits<float>::infinity(), depth);
                }
            }
            c = c / float(nSquare*nSquare);
            fb.setPixelColor(x, y, c);
        }
    }
    fb.exportAsPNG(output);

}