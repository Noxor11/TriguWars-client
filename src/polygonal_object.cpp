#include "polygonal_object.hpp"
#include "draw.hpp"
#include "text.hpp"
#include <iostream>
#include <string>

using graphics::draw_triangle;

void PolygonalObject::draw(const VirtualScreen &vscreen, bool rotate) {
  // graphics::Vector2 vertices[this->vertices_count];
  // for (int i = 0; i < this->vertices_count; i++) {
  //   auto v = b2Mul(this->body->GetTransform(), this->vertices[i]);
  //   // TODO: Escalar en base a vscreen
  //   if (!rotate) {
  //     vertices[i] = {vscreen.translate_x(v.x), vscreen.translate_y(v.y)};
  //     std::cout << v.x << "!!" << std::endl;
  //   } else {
  //     vertices[i] = {vscreen.translate_x(v.y), vscreen.translate_y(v.x)};
  //   }
  // }
    // draw_triangle(this->vertices[0].x, this->vertices[0].y,
    //             this->vertices[1].x, this->vertices[1].y,
    //             this->vertices[2].x, this->vertices[2].y,
    //             {255, 0, 0, 255});

    std::cout << this->vertices[0].x + 0.1f << "\n";
    graphics::text::draw_text(30, 100, {255, 255, 255, 255}, 
        std::string("v1-").append(std::to_string(this->vertices[0].x)), 30);

    graphics::text::draw_text(30, 150, {255, 255, 255, 255}, 
        std::string("v2-").append(std::to_string(this->vertices[1].x)), 30);

    graphics::text::draw_text(30, 200, {255, 255, 255, 255}, 
        std::string("v3-").append(std::to_string(this->vertices[2].x)), 30);

    graphics::draw_line(0, 55, 200, 55, {255, 255, 0, 255});

    graphics::draw_line(100, 100, this->vertices[0].x, this->vertices[0].y, {0, 255, 0, 255});
  // graphics::draw_vertices(vertices, this->vertices_count, this->color);
};

PolygonalObject::PolygonalObject(b2World* world, b2Body* body, b2Vec2* vertices, unsigned int vertices_count, const graphics::Color &color):
    Object(world, body, color), vertices(new b2Vec2[vertices_count]), vertices_count(vertices_count) {
        for (unsigned int i = 0; i < vertices_count; ++i){
            this->vertices[i] = vertices[i];
        }
    }

PolygonalObject::~PolygonalObject(){
  delete[] vertices;
}

