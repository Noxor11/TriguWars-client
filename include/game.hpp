#pragma once

#include "trigu.hpp"
#include "virtual_screen.hpp"
#include <box2d/box2d.h>
#include <vector>
#include <memory>
#include "polygonal_object.hpp"

class Game {
    public:

    b2World* world;
    VirtualScreen vscreen;
    std::vector<PolygonalObject> polygonal_objects;
    std::vector<Trigu> players;
    Trigu player;


    // Box2D recommends 8 velocity iterations
    int velocity_iterations;
    // Box2D recommends 3 position iterations
    int position_iterations;

    void update(float dt);
    void register_polygonal_object(const PolygonalObject& plobject);
    Game(const b2Vec2 &gravity, int velocity_iterations, int position_iterations);
    ~Game();
};
