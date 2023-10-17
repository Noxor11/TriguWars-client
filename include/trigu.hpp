#pragma once
#include <box2d/box2d.h>
#include "draw.hpp"

class Trigu {
    b2Body* body;

    Trigu(b2World world, float x, float y, float w, float h, float density, float friction, const graphics::Color& color);

    private:
    // La forma es inmutable
    b2PolygonShape shape;
};
