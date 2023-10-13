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
