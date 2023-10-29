#include "polygonal_object.hpp"
#include "dimensions.hpp"
#include "draw.hpp"
#include "text.hpp"
#include <iostream>
#include <string>

using graphics::draw_triangle;

#define RENDER_TOP screen % 2 != 0
#define RENDER_BOTTOM screen > 1

enum SCREENS {
  TOP     = 1,
  BOTTOM  = 2,
  BOTH    = 3
};

void PolygonalObject::draw(const VirtualScreen &vscreen, bool rotate) {
    graphics::Vector2 vertices[this->vertices_count];
    int screen = 0; // 0 = upper, 1 = lower, 2 = both
    #ifdef __3DS__
    float max_y = 0;
    float min_y = 0;
    #endif
    for (unsigned int i = 0; i < this->vertices_count; i++) {
      auto v = b2Mul(this->body->GetTransform(), this->vertices[i]);
      // TODO: Escalar en base a vscreen
      if (!rotate) {
        vertices[i] = {vscreen.translate_x(v.x), vscreen.translate_y(v.y)};
      } else {
        vertices[i] = {vscreen.translate_x((vscreen.height - v.x) * vscreen.scale), vscreen.translate_y(v.y * vscreen.scale)};
        #ifdef __3DS__
        if (i == 0) min_y = vertices[i].y;
        if (min_y > vertices[i].y) min_y = vertices[i].y;
        if (max_y < vertices[i].y) max_y = vertices[i].y;
        #endif
      }
    }

    #ifdef __3DS__
    if (max_y < TOP_SCREEN_HEIGHT) { // if the polygon is in the top screen
      screen = TOP;
      this->color = {255, 0, 0, 255};
    } else if (max_y > TOP_SCREEN_HEIGHT && min_y > TOP_SCREEN_HEIGHT) { // si el polígono está entremedias
      screen = BOTTOM;
      this->color = {255, 255, 0, 255};
    } else { // if the polygon is in the bottom screen
      screen = BOTH;
      this->color = {0, 255, 0, 255};
    }

    if (RENDER_TOP) {
      graphics::set_screen(graphics::TOP1);
      graphics::draw_vertices(vertices, this->vertices_count, this->color, this->filled);
    }

    if (RENDER_BOTTOM) {
      graphics::set_screen(graphics::BOTTOM);
      for (int i = 0; i < this->vertices_count; i++) {
        vertices[i].y -= BOTTOM_SCREEN_HEIGHT;
        vertices[i].x -= (TOP_SCREEN_WIDTH - BOTTOM_SCREEN_WIDTH) / 2;
      }
      graphics::draw_vertices(vertices, this->vertices_count, this->color, this->filled);
    }
    #endif

    #ifndef __3DS__
    graphics::draw_vertices(vertices, this->vertices_count, this->color, this->filled);
    #endif

};

PolygonalObject::PolygonalObject(b2World* world, b2Body* body, b2Vec2* vertices, unsigned int vertices_count, const graphics::Color &color, bool filled):
    Object(world, body, color, filled), vertices(vertices, vertices + vertices_count), vertices_count(vertices_count) {
    }

PolygonalObject::~PolygonalObject(){
}

PolygonalObject CreatePolygonalObject(b2World* world, b2Vec2* vertices, unsigned int vertices_count, float density, float friction, const graphics::Color &color, bool filled) {
    b2PolygonShape shape;
    shape.Set(vertices, vertices_count);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    b2Body* body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    fixtureDef.density = density;
    fixtureDef.friction = friction;

    body->CreateFixture(&fixtureDef);

    return PolygonalObject(world, body, vertices, vertices_count, color, filled);
}
