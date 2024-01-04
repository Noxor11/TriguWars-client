#include "bullet.hpp"
#include "game.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "object.hpp"
#include "trigu.hpp"
#include "polygonal_object.hpp"
#include "dimensions.hpp"
#include "input.hpp"
#include "player.hpp"
#include "screen_transitions.hpp"

#include <memory>
#include <chrono>

using std::to_string;

Game::Game(const b2Vec2 &gravity, int velocity_iterations = 8,
           int position_iterations = 3,
           const GameConfig::GameConfig &game_config)
    : world(new b2World(gravity)), vscreen(0, 0, 0, 0, 0.0f),
      player(register_object(CreateTriguPlayer(
          world, 0.1, 0.15, 0.1, 0.3, 1.0f, 0.3f,
          graphics::Color{0, 0, 255, 255}, &this->game_config))),
      velocity_iterations(velocity_iterations),
      position_iterations(position_iterations), game_config(game_config) {

  vscreen.width = 480;
  vscreen.height = 320;
  vscreen.offset_y = 0;
#if defined(__PSVITA__) || defined(__PC__)
  vscreen.scale = SCREEN_HEIGHT / vscreen.height;
  vscreen.offset_x = (SCREEN_WIDTH - vscreen.width * vscreen.scale) / 2;
#else
  // NOTE: 3DS has to handle offset in between screens
  vscreen.scale = 1.0f;
  vscreen.offset_x = 40;
#endif

  players.emplace_back(player);
}

Trigu* Game::create_trigu(float x, float y, float w, float h, float density, float friction, const graphics::Color& color){
    return register_object(CreateTrigu(world, x, y, w, h, density, friction, color));
}

Player* Game::create_triguplayer(float x, float y, float w, float h, float density, float friction, const graphics::Color& color){
    return register_object(CreateTriguPlayer(world, x, y, w, h, density, friction, color, &game_config));}

PolygonalObject* Game::create_polygonal_object(const b2Vec2* vertices, int vertices_count, float density, float friction, const graphics::Color& color, bool filled){
    return register_object(CreatePolygonalObject(world, vertices, vertices_count, density, friction, color, filled));
}

Bullet* Game::create_bullet(float x, float y, float radius, int resolution, b2Vec2 direction, float speed, float density, float friction, const graphics::Color& color, bool fill) {
    bullets.push_back(register_object(CreateBullet(world, x, y, radius, resolution, direction, speed, density, friction, color)));
    return bullets[bullets.size()-1];
}

template<Derived<Object> T>
T* Game::register_object(const T& object) {
    objects.emplace_back(std::make_shared<T>(object));
    return (T*)(objects[objects.size()-1].get());
}

auto proflogic = std::chrono::steady_clock::now();
auto profphys = std::chrono::steady_clock::now();
auto profdraw = std::chrono::steady_clock::now();

void Game::handle_player_move(){

    //auto vel = player.body->GetLinearVelocity();
    //player.body->SetLinearVelocity();

    if (game_config.movement_mode == GameConfig::MovementMode::THRUST_AND_BRAKES) {
        if (game_config.input_compatibility > GameConfig::InputCompatibility::DS) {
            player_speed += input::joystick1.y * (game_config.speed / 128.0f);
        } else {
            if (input::is_key_pressed(input::BUTTON_DPAD_DOWN)) {
                player_speed += -game_config.speed;
            } else if (input::is_key_pressed(input::BUTTON_DPAD_UP)) {
                player_speed += game_config.speed;
            }
        }

            //if (player_speed > game_config.top_speed || player_speed < -game_config.top_speed) {
            //    player_speed = (player_speed / abs(player_speed)) * game_config.top_speed;
            //    // Don't
            //} else {
                b2Vec2 force = b2Vec2(sin(player->body->GetAngle()) * player_speed, -cos(player->body->GetAngle()) * player_speed);
                player->body->SetLinearVelocity(force);
            //}
            //float new_speed = (force + player.body->GetLinearVelocity()).Length();
       // TODO
    } else if (game_config.movement_mode == GameConfig::MovementMode::JOYSTICK2_STRAFE) {
        if (game_config.input_compatibility <= GameConfig::InputCompatibility::PSP) {
            graphics::text::draw_text(10, 30, "! Joystick2 strafe is not possible in PSP compatibility mode or below", graphics::text::pt_to_size(30), false, graphics::Color::RED());
        } else {
            // TODO
        }
    }

    if (game_config.input_compatibility > GameConfig::InputCompatibility::DS) {
        player_rotation_speed += input::joystick1.x * (game_config.rotation_speed / 128.0f);
    } else {
        if (input::is_key_pressed(input::BUTTON_DPAD_DOWN)) {
            player_rotation_speed += -game_config.speed;
        } else if (input::is_key_pressed(input::BUTTON_DPAD_UP)) {
            player_rotation_speed += game_config.speed;
        }

    }


    //if (player_rotation_speed < game_config.rotation_top_speed && player_rotation_speed > -game_config.rotation_top_speed) {
        player->body->SetAngularVelocity(player_rotation_speed);
    //} else {
    //    player_rotation_speed = (player_rotation_speed / abs(player_rotation_speed)) * game_config.rotation_top_speed;
    //}
}

void Game::update(float dt) {
    time_accumulator += dt;

    proflogic = std::chrono::steady_clock::now();

    for(auto& obj : objects) {
        obj->update(dt);
    }
    //if (player_respawning) {
    //    respawn_timer_acum += dt;
    //    if (respawn_timer_acum > game_config.respawn_time) {
    //        switch (game_config.respawn_method) {
    //            case GameConfig::RespawnMethod::CENTER:
    //                player.body->SetTransform({0, 0}, 0);
    //                break;
    //        }

    //        player.body->SetEnabled(true);
    //        respawn_timer_acum = 0;
    //        player_respawning = false;
    //        player.hidden = false;
    //    }
    //}

    if (!player->is_dead && game_config.enable_barrier) {
        auto pos = player->body->GetPosition();
        if (pos.x < -game_config.barrier_distance || pos.x > game_config.barrier_distance
            || pos.y < -game_config.barrier_distance || pos.y > game_config.barrier_distance) {

            //player.body->SetEnabled(false);
            //player.body->SetTransform({0, 0}, 0);
            //player.body->SetLinearVelocity({0,0});
            //player.body->SetAngularVelocity(0);
            //player_speed = 0;
            //player_rotation_speed = 0;
            //player_respawning = true;
            //respawn_timer_acum = 0.0f;
            //player.hidden = true;
            player->kill();
        }
    }
    
    adjust_scale();

    player->handle_game_logic(dt, this);

    for (auto b : bullets) {
        b->handle_game_logic(dt, this);
    }

    //if (!player_respawning) {
    //    handle_player_move();
    //}

    float time_logic = (std::chrono::duration_cast<std::chrono::nanoseconds>)(std::chrono::steady_clock::now() - proflogic).count() / 10E5;

    profphys = std::chrono::steady_clock::now();
    world->Step(dt, velocity_iterations, position_iterations);

    float time_physics = (std::chrono::duration_cast<std::chrono::nanoseconds>)(std::chrono::steady_clock::now() - profphys).count() / 10E5;

    // for (float fx = -1.5f * scale; fx < 1.5f * scale; fx+= 0.1f) {
    //     for (float fy = -1.0f * scale; fy < 1.0f * scale; fy += 0.1f) {
    //         graphics::draw_rectangle(vscreen.translate_x(fx * scale), vscreen.translate_y(fy * scale), 0.05f * scale * vscreen.scale, 0.05f * scale * vscreen.scale, graphics::Color {100, 100, 100});
    //     }
    // }
    //scale_t += dt;
    //if (scale != target_scale) {
    //

    profdraw = std::chrono::steady_clock::now();

    if (scale_grow_direction < 0.0f && scale <= target_scale) {
        scale = target_scale;
        scale_grow_direction = 0.0f;
    } else if (scale_grow_direction > 0.0f && scale >= target_scale) {
        scale = target_scale;
        scale_grow_direction = 0.0f;
    }

    // v = (x - x0) / t
    scale += dt * scale_grow_direction * ( abs(scale - target_scale) / (scale_grow_duration) );

    // if (input::is_key_pressed(input::Buttons::BUTTON_CONFIRM)) {
    //     auto obj = this->create_trigu(20, 20, 20, 40, 0.1f, 0.3f, graphics::Color::BLUE());
    //     const auto pos = player->body->GetPosition();
    //     obj->body->SetTransform({pos.x, pos.y}, obj->body->GetAngle());
    // }

    for(auto& obj : objects) {
        #ifdef __3DS__
        obj->draw(vscreen, true, scale);
        #else
        obj->draw(vscreen, false, scale);
        #endif
    }

    if (game_config.enable_barrier) {
        float color_t = 1.0f;
        if (game_config.barrier_animation) {
            color_t = abs(sin(fmod(time_accumulator, game_config.barrier_animation_duration) / game_config.barrier_animation_duration * 3.14f));
        }
        graphics::Color color = {(int)round(color_t * 255.0f), 0, 0, 255};

        auto distance = scale * (vscreen.width / 2);
        if (distance > game_config.barrier_distance || distance < -game_config.barrier_distance) {
            #ifdef __3DS__
            float prev_offset = vscreen.offset_x;
            for(int i = 0; i < 2; i++) {
                if (i == 1) {
                    graphics::set_screen(graphics::BOTTOM);
                    vscreen.offset_x = 0;
                    vscreen.offset_y = -BOTTOM_SCREEN_HEIGHT;
                } else {
                    graphics::set_screen(graphics::TOP1);
                }
            // Izquierda
            graphics::draw_rectangle(
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.height/2) * vscreen.scale + vscreen.offset_x,
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.width/2) * vscreen.scale + vscreen.offset_y,
                game_config.barrier_distance*2 * scale * vscreen.scale,
                game_config.barrier_width * scale * vscreen.scale,
                color
            );
            // Arriba
            graphics::draw_rectangle(
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.height/2) * vscreen.scale + vscreen.offset_x,
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.width/2) * vscreen.scale + vscreen.offset_y,
                game_config.barrier_width * scale * vscreen.scale,
                game_config.barrier_distance*2 * scale * vscreen.scale,
                color
            );
            // Derecha
            graphics::draw_rectangle(
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.height/2) * vscreen.scale + vscreen.offset_x,
                ((game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.width/2) * vscreen.scale + vscreen.offset_y,
                game_config.barrier_distance*2 * scale * vscreen.scale,
                game_config.barrier_width * scale * vscreen.scale,
                color
            );
            // Abajo
            graphics::draw_rectangle(
                ((game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.height/2) * vscreen.scale + vscreen.offset_x,
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.width/2) * vscreen.scale + vscreen.offset_y,
                game_config.barrier_width * scale * vscreen.scale,
                (game_config.barrier_distance * 2 + game_config.barrier_width) * scale * vscreen.scale,
                color
            );

            }

            vscreen.offset_x = prev_offset;
            vscreen.offset_y = 0;

            graphics::set_screen(graphics::TOP1);

            #else
            // Izquierda
            graphics::draw_rectangle(
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.width/2) * vscreen.scale + vscreen.offset_x,
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.height/2) * vscreen.scale + vscreen.offset_y,
                game_config.barrier_width * scale * vscreen.scale,
                game_config.barrier_distance*2 * scale * vscreen.scale,
                color
            );
            // Arriba
            graphics::draw_rectangle(
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.width/2) * vscreen.scale + vscreen.offset_x,
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.height/2) * vscreen.scale + vscreen.offset_y,
                game_config.barrier_distance*2 * scale * vscreen.scale,
                game_config.barrier_width * scale * vscreen.scale,
                color
            );
            // Derecha
            graphics::draw_rectangle(
                ((game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.width/2) * vscreen.scale + vscreen.offset_x,
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.height/2) * vscreen.scale + vscreen.offset_y,
                game_config.barrier_width * scale * vscreen.scale,
                game_config.barrier_distance*2 * scale * vscreen.scale,
                color
            );
            // Abajo
            graphics::draw_rectangle(
                ((-game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.width/2) * vscreen.scale + vscreen.offset_x,
                ((game_config.barrier_distance - game_config.barrier_width) * scale + vscreen.height/2) * vscreen.scale + vscreen.offset_y,
                (game_config.barrier_distance * 2 + game_config.barrier_width) * scale * vscreen.scale,
                game_config.barrier_width * scale * vscreen.scale,
                color
            );
            #endif
        }
    }

    if (player->is_dead) {
        graphics::draw_rectangle(vscreen.offset_x, (vscreen.height - 20) * vscreen.scale,
                                 (player->respawn_accumulator / game_config.respawn_time) * vscreen.width * vscreen.scale, vscreen.height * vscreen.scale, graphics::Color(100, 100, 255, 255 * 0.7f));
    }
    graphics::text::draw_text(170, 170, to_string(game_config.respawn_time));

    float time_draw = (std::chrono::duration_cast<std::chrono::nanoseconds>)(std::chrono::steady_clock::now() - profdraw).count() / 10E5;

    graphics::text::draw_text(10, SCREEN_HEIGHT-120, std::string("logic ").append(std::to_string(time_logic)), 30, false, graphics::Color::BLUE());
    graphics::text::draw_text(10, SCREEN_HEIGHT-90,  std::string("phys  ").append(std::to_string(time_physics)), 30, false, graphics::Color::GREEN());
    graphics::text::draw_text(10, SCREEN_HEIGHT-60,  std::string("draw  ").append(std::to_string(time_draw)), 30, false, graphics::Color::YELLOW());

}

void Game::adjust_scale() {
    float min_x = -0.1;
    float max_x = 0.1;
    float min_y = -0.1;
    float max_y = 0.1;

    for (auto& obj : objects) {
        if (((std::static_pointer_cast<PolygonalObject>)(obj))->vertices != NULL) {
            auto pobj = (std::static_pointer_cast<PolygonalObject>)(obj);
            for (unsigned int i = 0; i < pobj->vertices_count; i++) {
                auto v = b2Mul(pobj->body->GetTransform(), pobj->vertices[i]);
                if (v.x < min_x) {
                   min_x = v.x;
                } else if (v.x > max_x) {
                   max_x = v.x;
                }

                if (v.y < min_y) {
                    min_y = v.y;
                } else if (v.y > max_y) {
                    max_y = v.y;
                }
            }
        }
    }

    float scale_x = 0;
    float scale_y = 0;
    auto distance = game_config.barrier_distance * game_config.camera_barrier_percentage;
    bool abnormal_adjust = false;
    if (game_config.enable_barrier && (max_x > distance || min_x < -distance || max_y > distance || min_y < -distance)) {
        scale_x = (vscreen.width / 2) / game_config.barrier_distance * (1.0 - game_config.camera_barrier_zoomout_margin);
        scale_y = (vscreen.height / 2) / game_config.barrier_distance * (1.0 - game_config.camera_barrier_zoomout_margin);
        abnormal_adjust = true;
    } else {
        float scale_min_x = -(vscreen.width / 2) / min_x;
        float scale_max_x = (vscreen.width / 2) / max_x;
        float scale_min_y = -(vscreen.height / 2) / min_y;
        float scale_max_y = (vscreen.height / 2) / max_y;

        scale_x = 0;
        scale_y = 0;

        if (scale_min_x < scale_max_x) {
            scale_x = scale_min_x;
        } else {
            scale_x = scale_max_x;
        }

        if (scale_min_y < scale_max_y) {
            scale_y = scale_min_y;
        } else {
            scale_y = scale_max_y;
        }
    }

    if (scale_x < scale_y) {
        target_scale = scale_x;
    } else {
        target_scale = scale_y;
    };

    if (scale > target_scale) {
        scale_grow_direction = -1.0;
    } else if (scale < target_scale) {
        scale_grow_direction = 1.0;
        if (!abnormal_adjust) {
            target_scale *= 0.9;
        }
    } else {
        return;
    }

}

Game::~Game(){
    delete world;
}
