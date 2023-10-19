#pragma once

#include "draw.hpp"
#include "virtual_screen.hpp"
#include <box2d/box2d.h>
#include <type_traits>

class Object {
    public:
        b2World* world;
        b2Body* body;
        graphics::Color color;

    public:
        Object(b2World* world, b2Body* body, const graphics::Color &color): world(world), body(body), color(color) {};
        ~Object();

        virtual void update() {};
        virtual void draw(const VirtualScreen &vscreen, bool rotate = false) {};
};
