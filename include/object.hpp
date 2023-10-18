#pragma once

#include "draw.hpp"
#include <box2d/box2d.h>

class Object {
    public:
        b2World* world;
        b2Body* body;
        graphics::Color color;

    public:
        Object(b2World* world, b2Body* body, const graphics::Color &color): world(world), body(body), color(color) {};
        ~Object();
};
