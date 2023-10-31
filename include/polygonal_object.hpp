#pragma once

#include "object.hpp"
#include <box2d/b2_math.h>
#include <cstring>
#include <vector>

class PolygonalObject : public Object {
    public:
    b2Vec2* vertices;
    unsigned int vertices_count;

    PolygonalObject(b2World* world, b2Body* body, b2Vec2* vertices, unsigned int vertices_count, const graphics::Color &color, bool filled = true);
    PolygonalObject(const PolygonalObject& other);
    PolygonalObject& operator=(const PolygonalObject& other);

    ~PolygonalObject();
    virtual void draw(const VirtualScreen &vscreen, bool rotate = false, float scale = 1.0) override;
};

PolygonalObject CreatePolygonalObject(b2World* world, b2Vec2* vertices, unsigned int vertices_count, float density, float friction, const graphics::Color &color, bool filled);
