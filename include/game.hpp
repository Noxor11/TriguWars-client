#pragma once

#include "virtual_screen.hpp"
#include <box2d/box2d.h>
#include <vector>
#include "polygonal_object.hpp"

class Game {
    public:

    std::vector<PolygonalObject*> polygonal_objects;

    b2World world;
    VirtualScreen vscreen;

    // Box2D recommends 8 velocity iterations
    int velocity_iterations;
    // Box2D recommends 3 position iterations
    int position_iterations;

    void update(float dt);
    void register_polygonal_object(PolygonalObject* plobject);
    Game(const b2Vec2 &gravity, int velocity_iteraitons, int position_iterations);

};
