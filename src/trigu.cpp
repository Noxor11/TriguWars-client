#include "trigu.hpp"
#include "draw.hpp"
#include "virtual_screen.hpp"

void Trigu::render(VirtualScreen &vscreen) {
    /*
    Puntos:
        x, y+h
        x + w/2, y
        x+w, y+h
    */

    float tx = vscreen.translate_x(this->x);
    float ty = vscreen.translate_y(this->y);
    float tw = vscreen.translate_w(this->w);
    float th = vscreen.translate_h(this->h);

    graphics::draw_triangle(
                            tx + tw/2.0f, ty,
                            tx + tw, ty + th,
                            tx, ty + th,
                            this->color);
}

Trigu::Trigu(float x, float y, float w, float h, const Color &color) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->color = color;
}
