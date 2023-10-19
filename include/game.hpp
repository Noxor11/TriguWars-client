#pragma once

#include "trigu.hpp"
#include "virtual_screen.hpp"
#include <box2d/box2d.h>
#include <vector>
#include <memory>
#include "object.hpp"

class Game {
    public:

    b2World* world;
    VirtualScreen vscreen;
    std::vector<std::shared_ptr<Object>> objects;
    std::vector<Trigu> players;
    Trigu player;


    // Box2D recommends 8 velocity iterations
    int velocity_iterations;
    // Box2D recommends 3 position iterations
    int position_iterations;

    void update(float dt);
    void register_object(const Object& object);
    Game(const b2Vec2 &gravity, int velocity_iterations, int position_iterations);
    ~Game();
};
