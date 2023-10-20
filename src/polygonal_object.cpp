#include "polygonal_object.hpp"
#include "draw.hpp"
#include "text.hpp"
#include <iostream>
#include <string>

using graphics::draw_triangle;

void PolygonalObject::draw(const VirtualScreen &vscreen, bool rotate) {
    graphics::Vector2 vertices[this->vertices_count];
    for (int i = 0; i < this->vertices_count; i++) {
      auto v = b2Mul(this->body->GetTransform(), this->vertices[i]);
      // TODO: Escalar en base a vscreen
      if (!rotate) {
        vertices[i] = {vscreen.translate_x(v.x * vscreen.scale), vscreen.translate_y(v.y * vscreen.scale)};
        std::cout << v.x << "!!" << std::endl;
      } else {
        vertices[i] = {vscreen.translate_x(v.y * vscreen.scale), vscreen.translate_y(v.x * vscreen.scale)};
      }
    }
    // draw_triangle(this->vertices[0].x, this->vertices[0].y,
    //             this->vertices[1].x, this->vertices[1].y,
    //             this->vertices[2].x, this->vertices[2].y,
    //             {255, 0, 0, 255});

    graphics::draw_vertices(vertices, this->vertices_count, this->color);
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

