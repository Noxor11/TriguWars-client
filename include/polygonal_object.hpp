#pragma once

#include "object.hpp"
#include <box2d/b2_math.h>
#include <cstring>

class PolygonalObject : public Object {
    public:
    b2Vec2* vertices;
    unsigned int vertices_count;

    PolygonalObject(b2World* world, b2Body* body, b2Vec2* vertices, unsigned int vertices_count, const graphics::Color &color);
    ~PolygonalObject();
    virtual void draw(const VirtualScreen &vscreen, bool rotate = false) override;    
};
