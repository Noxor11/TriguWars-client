#include "virtual_screen.hpp"

float VirtualScreen::translate_x(float x) {
    return this->offset_x + x;
};

float VirtualScreen::translate_y(float y) {
    return this->offset_y + y;
};

float VirtualScreen::translate_h(float h) {
    return this->scale * h;
}

float VirtualScreen::translate_w(float w) {
    return this->scale * w;
}

VirtualScreen::VirtualScreen(float x, float y, float w, float h, float scale) {
    offset_x = x;
    offset_y = y;
    width = w;
    height = h;
    this->scale = scale;
}
