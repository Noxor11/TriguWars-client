#include "trigu.hpp"
#include "draw.hpp"
#include "virtual_screen.hpp"
#include <cmath>

using namespace graphics;



Vector2& rotate_vector(Vector2& vec, Vector2 center, float angle) {
    // https://en.wikipedia.org/wiki/Rotation_matrix
    // https://danceswithcode.net/engineeringnotes/rotations_in_2d/rotations_in_2d.html
    
    vec = {
        (vec.x - center.x) * std::cos(angle) + (vec.y - center.y) * std::sin(angle) + center.x,
        (vec.x - center.x) * -std::sin(angle) + (vec.y - center.y) * std::cos(angle) + center.y
    };

    return vec;
};

void Trigu::update_rotation() {
   calculate_vertices();
   auto& center = calculate_center();

   rotate_vector(vertices[0], center, this->rotation);
   rotate_vector(vertices[1], center, this->rotation);
   rotate_vector(vertices[2], center, this->rotation);
}

void Trigu::update_params(){
    calculate_center();
    calculate_vertices();
}

void Trigu::set_vector2(const graphics::Vector2 &vector2) {
    this->vector2 = vector2;
    update_params();
}

void Trigu::set_rotation(float rotation) {
    this->rotation = rotation;
    update_rotation();
    update_params();
}

void Trigu::move_x_by(float units){
    if (units != 0) {
        x += units;
        update_params();
    }
}

void Trigu::move_y_by(float units){
    if (units != 0){
        y -= units;
        update_params();
    }
}


void Trigu::set_x(float x) {
    this->x = x;
    update_params();
}

void Trigu::set_y(float y) {
    this->y = y;
    update_params();
}

void Trigu::rotate_by(float rotation){
    this->rotation += rotation;
    update_rotation();

}

void Trigu::render(const VirtualScreen& vscreen) {

    graphics::draw_triangle(
                        vscreen.translate_x(vertices[0].x), vscreen.translate_y(vertices[0].y),
                        vscreen.translate_x(vertices[1].x), vscreen.translate_y(vertices[1].y),
                        vscreen.translate_x(vertices[2].x), vscreen.translate_y(vertices[2].y),
                        this->color);
}

std::array<graphics::Vector2, 3>& Trigu::calculate_vertices(){

    /*
    Vertices:
        x, y+h
        x + w/2, y
        x+w, y+h
    */
    
    Vector2 vec1 = {x + w / 2.0f, y};
    Vector2 vec2 = {x + w, y + h};
    Vector2 vec3 = {x, y + h};

    vertices[0] = vec1;
    vertices[1] = vec2;
    vertices[2] = vec3;

    return vertices;
}

Trigu::Trigu(float x, float y, float w, float h, float rotation, const Color& color) :
    Object(x, y, w, h, rotation), color(color) {
            
        update_params();
    }
