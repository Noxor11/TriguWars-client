#include "virtual_screen.hpp"

float VirtualScreen::translate_x(float x) const {
    return this->offset_x + x;
};

float VirtualScreen::translate_y(float y) const {
    return this->offset_y + y;
};

float VirtualScreen::translate_h(float h) const {
    return this->scale_h * h;
}

float VirtualScreen::translate_w(float w) const {
    return this->scale_w * w;
}

VirtualScreen::VirtualScreen(float x, float y, float w, float h, float scale) :
    offset_x{x}, offset_y{y}, width{w}, height{h}, scale_w{scale}, scale_h{scale}, scale{scale} {}
