// #include "framebuffer.hpp"
// #include "triangle.hpp"
// #include "perspectiveCamera.hpp"


// void testTriangleIntersect (triangle t, framebuffer fb, perspectiveCamera p, int nx, int ny, color bg) {
//     fb.clearToColor(bg);
    
//     for (int x=0; x<nx; x++) {
//         for(int y=0; y<ny; y++) {
//             float tmax = 1000000.0f;
//             ray r;
//             p.generateRay(x, y, r);
//             color rayColor;
//             if (t.intersect(r, 1.0f, tmax)) {
//                 rayColor = t.getColor();
//             } else {
//                 rayColor = bg;
//             }
//             fb.setPixelColor(x, y, rayColor);
//         }
//     }
//     fb.exportAsPNG("AwesomeTriangle.png");
// }

// int main () {
// int pixelHeight = 200;
//     int pixelWidth = 200;
//     color skyBlue(0.529f, 0.808f, 0.922f);
//     framebuffer fb(pixelWidth, pixelHeight);
//     triangle t(point(0.0f, 1.0f, -15.0f), point(1.0f, -1.0f, -15.0f), point(-1.0f, -1.0f, -15.0f), color(1.0f, 1.0f, 0.0f));
//     perspectiveCamera p(pixelWidth, pixelHeight, 0.5f, 0.5f, 1.0f, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
//     testTriangleIntersect(t, fb, p, pixelWidth, pixelHeight, skyBlue);
// }