#include "Framebuffer.hpp"

Framebuffer::Framebuffer() : width(100), height(100), fbStorage(width*height){}
Framebuffer::Framebuffer(int w, int h) : width(w), height(h), fbStorage(width*height){}

void::Framebuffer::clearToColor(color c) {
    for (auto i : fbStorage) {
        i = c;
    }
}

void::Framebuffer::clearToVerticalGradient(color top, color bottom){
    for (int y; y++; y > height) {
        for (int x; x++; x > width) {
            float t = y / height;
            color c1 = top;
            color c2 = bottom;
            (c1 * t);
            (c2 / t);
            c1+=c2;
            fbStorage[(y*width)+x] = c1;
        }
    }
}

void::Framebuffer::clearToHorizontalGradient(color left, color right){
    for (int y; y++; y > height) {
        for (int x; x++; x > width) {
            float t = x / width;
            color c1 = left;
            color c2 = right;
            (c1 * t);
            (c2 / t);
            c1+=c2;
            fbStorage[(y*width)+x] = c1;
        }
    }
}

void::Framebuffer::setPixelColor(int x, int y, color c){
    fbStorage[(y * width) + x] = c;
}

void::Framebuffer::exportAsPNG(std::string filename) {
    png::image< png::rgb_pixel > imData( width, height );
    for (size_t y = 0; y < imData.get_height(); ++y)
    {
        for (size_t x = 0; x < imData.get_width(); ++x)
	    {
            color c = fbStorage[(y*width)+x];
            int r = c.r() * 255;
            int g = c.g() * 255;
            int b = c.b() * 255;
            imData[y][x] = png::rgb_pixel(r, g, b);
	    }
    }
    imData.write(filename);
}