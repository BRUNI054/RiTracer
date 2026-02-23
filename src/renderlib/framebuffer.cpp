#include "framebuffer.hpp"
#include "./../png++/png.hpp"

framebuffer::framebuffer() : width(100), height(100), fbStorage(width*height){}
framebuffer::framebuffer(int w, int h) : width(w), height(h), fbStorage(width*height){}

void::framebuffer::clearToColor(color c) {
    for (int i = 0; i < (width * height); i++) {
        fbStorage[i] = c;
    }
}

void::framebuffer::clearToVerticalGradient(color top, color bottom){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float t = float(y) / float(height);
            color c = ((1-t)*bottom) + (t*top);
            fbStorage[(y*width)+x] = c;
        }
    }
}

void::framebuffer::clearToHorizontalGradient(color left, color right){
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float t = float(x) / float(width);
            color c = ((1-t)*right) + (t*left);
            fbStorage[(y*width)+x] = c;
        }
    }
}

void::framebuffer::setPixelColor(int x, int y, color c){
    if (c.x() > 1.0f) {
        c.set_x(1.0f);
    }if (c.y() > 1.0f) {
        c.set_y(1.0f);
    }if (c.z() > 1.0f) {
        c.set_z(1.0f);
    }
    fbStorage[(y * width) + x] = c;
}

void::framebuffer::exportAsPNG(std::string filename) {
    png::image< png::rgb_pixel > imData( width, height );
    for (size_t y = imData.get_height()-1; y > 0; y--)
    {
        for (size_t x = 0; x < imData.get_width(); x++)
	    {
            color c = fbStorage[(y*width)+x];
            int r = int(c.r() * 255);
            int g = int(c.g() * 255);
            int b = int(c.b() * 255);
            imData[height-y][x] = png::rgb_pixel(r, g, b);
	    }
    }
    imData.write(filename);
}