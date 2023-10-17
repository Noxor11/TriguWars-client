#pragma once

#include "draw.hpp"
#include "virtual_screen.hpp"

#include <functional>
#include <box2d/box2d.h>

class Object {
    public:
        b2Body* body;
        b2Vec2* vertices;
        signed int vertices_count;

        std::function<void(const b2Vec2*)> drawing_function;
   
    public:

        Object(b2Body* body, std::function<void(const b2Vec2*)> drawing_function);
        ~Object();

        void calculate_vertices();
        void draw();
};
