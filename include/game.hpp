#pragma once

#include "virtual_screen.hpp"
#include <box2d/box2d.h>

class Game {
    public:

    b2World world;
    VirtualScreen vscreen;

    // Box2D recommends 8 velocity iterations
    int velocity_iterations;
    // Box2D recommends 3 position iterations
    int position_iterations;

    void update(float dt);
    Game(const b2Vec2 &gravity, int velocity_iteraitons, int position_iterations);

};
