#pragma once
#include <box2d/box2d.h>
#include "draw.hpp"
#include "polygonal_object.hpp"

class Trigu : public PolygonalObject {

  public:
    Trigu(const Trigu &) = default;
    Trigu(Trigu &&) = default;
    Trigu(b2World* world, b2Vec2* vertices, unsigned int vertices_count, b2Body* body, const graphics::Color &color)
        : PolygonalObject(world, body, vertices, vertices_count, color) {}
};

Trigu CreateTrigu(b2World* world, float x, float y, float w, float h, float density, float friction, const graphics::Color& color);
