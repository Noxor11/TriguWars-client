#pragma once

#include "object.hpp"
#include <box2d/b2_math.h>

class PolygonalObject : public Object {
    public:
    b2Vec2* vertices;
    unsigned int vertices_count;

    PolygonalObject(b2World* world, b2Body* body, b2Vec2* vertices, unsigned int vertices_count, const graphics::Color &color):
        Object(world, body, color), vertices(vertices), vertices_count(vertices_count) {}


    virtual void draw(const VirtualScreen &vscreen, bool rotate = false) override;
};
