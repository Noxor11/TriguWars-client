#pragma once

#include "polygonal_object.hpp"

class ConnectedLineObject : public PolygonalObject {

  public:   

    ConnectedLineObject(const ConnectedLineObject &) = default;
    ConnectedLineObject(ConnectedLineObject &&) = default;
    ConnectedLineObject(b2World* world, b2Vec2* vertices, int vertices_count, float density, float friction, const graphics::Color& color);

    virtual void draw(const VirtualScreen &vscreen, bool rotate = false) override;    

};