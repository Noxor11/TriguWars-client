#include "object.hpp"
#include "draw.hpp"
#include "virtual_screen.hpp"
#include <cmath>

using namespace graphics;

// Vector2 rotate_vector(Vector2 vec, Vector2 center, float angle) {
//     // https://en.wikipedia.org/wiki/Rotation_matrix
//     // https://danceswithcode.net/engineeringnotes/rotations_in_2d/rotations_in_2d.html
//     return {
//         (vec.x - center.x) * std::cos(angle) + (vec.y - center.y) * std::sin(angle) + center.x,
//         (vec.x - center.x) * -std::sin(angle) + (vec.y - center.y) * std::cos(angle) + center.y
//     };
// };

const Vector2& Object::calculate_center() {
    center = Vector2{x + w / 2.0f, y + h / 2.0f};
    return center;
}

const graphics::Vector2& Object::get_vector2() const {
    return vector2;
}


float Object::get_rotation() const {
    return rotation;
}

void Object::set_rotation(float rotation){
    this->rotation = rotation;
}

void Object::move_x_by(float units){
    x += units;
}

void Object::move_y_by(float units){
    y -= units;
}

Object::Object(float x, float y, float w, float h, float rotation) :
    x{x}, y{y}, w{w}, h{h}, rotation{rotation} {}
