#include "trigu.hpp"
#include "draw.hpp"
#include "virtual_screen.hpp"
#include <cmath>

using namespace graphics;

Vector2 rotate_vector(Vector2 vec, Vector2 center, float angle) {
    // https://en.wikipedia.org/wiki/Rotation_matrix
    // https://danceswithcode.net/engineeringnotes/rotations_in_2d/rotations_in_2d.html
    return {
        (vec.x - center.x) * std::cos(angle) + (vec.y - center.y) * std::sin(angle) + center.x,
        (vec.x - center.x) * -std::sin(angle) + (vec.y - center.y) * std::cos(angle) + center.y
    };
};


void Trigu::render(VirtualScreen& vscreen) {
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

    Vector2 vec1 = {tx + tw / 2.0f, ty};
    Vector2 vec2 = {tx + tw, ty + th};
    Vector2 vec3 = {tx, ty + th};
    Vector2 center = {tx + tw / 2.0f, ty + h / 2.0f};

    vec1 = rotate_vector(vec1, center, this->rotation);
    vec2 = rotate_vector(vec2, center, this->rotation);
    vec3 = rotate_vector(vec3, center, this->rotation);

    graphics::draw_triangle(
                            vec1.x, vec1.y,
                            vec2.x, vec2.y,
                            vec3.x, vec3.y,
                            this->color);
}


Trigu::Trigu(float x, float y, float w, float h, float rotation, const Color& color) :
    x{x}, y{y}, w{w}, h{h}, rotation{rotation}, color{color} {}