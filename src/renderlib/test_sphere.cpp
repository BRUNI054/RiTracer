// #include "framebuffer.hpp"
// #include "sphere.hpp"
// #include "perspectiveCamera.hpp"

// void testSphereIntersect(sphere s, framebuffer fb, perspectiveCamera p, int nx, int ny, color bg) {
//     fb.clearToColor(bg);
//     for (int x=0; x<nx; x++) {
//         for(int y=0; y<ny; y++) {
//             float tmax = 1000000.0f;
//             ray r;
//             p.generateRay(x, y, r);
//             color rayColor;
//             if (s.intersect(r, 1.0f, tmax)) {
//                 rayColor = s.getColor();
//             } else {
//                 rayColor = bg;
//             }
//             fb.setPixelColor(x, y, rayColor);
//         }
//     }
//     fb.exportAsPNG("AwesomeSphere.png");
// }

// int main() {
//     int pixelHeight = 200;
//     int pixelWidth = 200;
//     color skyBlue(0.529f, 0.808f, 0.922f);
//     framebuffer fb(pixelWidth, pixelHeight);
//     sphere s(point(0.0f, 0.0f, -10.0f), 1.0f, color(1.0f, 1.0f, 0.0f));
//     perspectiveCamera p(pixelWidth, pixelHeight, 0.5f, 0.5f, 1.0f, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
//     //perspectiveCamera p;
//     testSphereIntersect(s, fb, p, pixelWidth, pixelHeight, skyBlue);
// }