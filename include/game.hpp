#pragma once

#include "trigu.hpp"
#include "virtual_screen.hpp"
#include <box2d/box2d.h>
#include <vector>
#include <memory>
#include "object.hpp"


template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

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
    Trigu* create_trigu(float x, float y, float w, float h, float density, float friction, const graphics::Color& color);
    PolygonalObject* create_polygonal_object(b2Vec2* vertices, int vertices_count, float density, float friction, const graphics::Color& color, bool fill);

    template<Derived<Object> T>
    T* register_object(const T& object);
    Game(const b2Vec2 &gravity, int velocity_iterations, int position_iterations);
    ~Game();
};
