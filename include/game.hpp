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
    enum class MovementMode {THRUST_AND_BRAKES, JOYSTICK2_STRAFE};
    enum class KillCondition {BULLET, CHASE, NONE};
    enum class InputCompatibility {PSP, DS, NO_TRIGGERS, FULL_GAMEPAD};
    /*
      RespawnMethod: Method to use to determine the respawn position for an object

      Center: Respawn on the absolute center
      Random: Respawn on a random position, on a radius defined by the current scale
      Equidistant: Calculate an equidistant position in relation to other objects
    */
    enum class RespawnMethod {CENTER, RANDOM, EQUDISTANT};

    struct GameConfig {
        // TODO: Air friction not implemented
        float air_friction = 0.0f;
        // TODO: JOYSTICK2_STRAFE not implemented
        MovementMode movement_mode = MovementMode::THRUST_AND_BRAKES;
        // TODO: Not implemented
        KillCondition kill_condition = KillCondition::BULLET;
        float top_speed = 0.070f;
        float speed = 0.005f;
        float rotation_speed = 0.02f;
        float rotation_top_speed = 0.08f;
        InputCompatibility input_compatibility = InputCompatibility::NO_TRIGGERS;
        bool enable_barrier = true;
        bool barrier_animation = true;
        // Duration of a cycle of the barrier animation, in seconds
        float barrier_animation_duration = 2.0f;
        // Distance from center where the kill barrier resides
        float barrier_distance = 5.0f;
        float barrier_width = 0.1f;
        // Percentage of distance that the farthest object has to be for the
        // camera too zoom out all the way to the barrier
        // (For example, if the barrier is 1000 units away and this is set to 0.7f,
        // the camera would zoom-out to the barrier at 700 units)
        float camera_barrier_percentage = 0.7f;
        // Percentage of margin to add when zooming-out to show the barrier
        float camera_barrier_zoomout_margin = 0.2f;
        // Respawn time in seconds
        float respawn_time = 1.0f;
        // The method which the games uses to determine the respawn position
        RespawnMethod respawn_method = RespawnMethod::CENTER;
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
    float scale_grow_duration = 1.0f;
    float scale_grow_direction = 0.0f;
    float target_scale = 1.0f;

    float player_speed = 0;
    float player_rotation_speed = 0;

    float time_accumulator = 0;

    GameConfig::GameConfig game_config;

    void handle_player_move();

    void update(float dt);
    Trigu* create_trigu(float x, float y, float w, float h, float density, float friction, const graphics::Color& color);
    PolygonalObject* create_polygonal_object(const b2Vec2* vertices, int vertices_count, float density, float friction, const graphics::Color& color, bool fill);

    template<Derived<Object> T>
    T* register_object(const T& object);
    void adjust_scale();
    Game(const b2Vec2 &gravity, int velocity_iterations, int position_iterations, GameConfig::GameConfig game_config = GameConfig::GameConfig());
    ~Game();
};
