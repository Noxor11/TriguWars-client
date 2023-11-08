#pragma once

#include "draw.hpp"
#include "virtual_screen.hpp"
#include <box2d/box2d.h>
#include <type_traits>

class Object {
    public:
        b2World* const world;
        b2Body* const body;
        graphics::Color color;
        bool filled;
        bool hidden = false;

    public:
        Object(b2World* const world, b2Body* const body, const graphics::Color &color, bool filled = true):
            world(world), body(body), color(color), filled(filled) {};
        ~Object();

        virtual void update(float dt) {};
        virtual void draw(const VirtualScreen &vscreen, bool rotate = false, float scale = 1.0) {};
};
