#pragma once

#include "trigu.hpp"
#include "virtual_screen.hpp"
#include <box2d/box2d.h>
#include <vector>
#include <memory>
#include "object.hpp"
#include "screen_transitions.hpp"

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

namespace GameConfig {
    enum MovementMode {THRUST_AND_BRAKES, JOYSTICK2_STRAFE};
    enum KillCondition {BULLET, CHASE, NONE};
    struct GameConfig {
        float air_friction = 0.0f;
        MovementMode movement_mode = THRUST_AND_BRAKES;
        KillCondition kill_condition = BULLET;
        float speed = 0.05f;
        float rotation_speed = 0.05f;
    };

}



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

    // adjusts automatically with Game::adjust_scale
    float scale = 1.0f;
    // In seconds
    float scale_grow_duration = 4.0f;
    float scale_grow_direction = 0.0f;
    float target_scale = 1.0f;

    void update(float dt);
    Trigu* create_trigu(float x, float y, float w, float h, float density, float friction, const graphics::Color& color);
    PolygonalObject* create_polygonal_object(const b2Vec2* vertices, int vertices_count, float density, float friction, const graphics::Color& color, bool fill);

    template<Derived<Object> T>
    T* register_object(const T& object);
    void adjust_scale();
    Game(const b2Vec2 &gravity, int velocity_iterations, int position_iterations);
    ~Game();
};
