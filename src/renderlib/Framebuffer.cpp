#include "Framebuffer.hpp"

Framebuffer::Framebuffer() : width(100), height(100), fbStorage(width*height){}
Framebuffer::Framebuffer(int w, int h) : width(w), height(h), fbStorage(width*height){}