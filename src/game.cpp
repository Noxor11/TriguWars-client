#include "game.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "object.hpp"
#include "trigu.hpp"
#include "polygonal_object.hpp"
#include "dimensions.hpp"
#include "title_screen.hpp"
#include "input.hpp"
#include "settings_screen.hpp"

#include <memory>


Game::Game(const b2Vec2 &gravity, int velocity_iterations = 8, int position_iterations = 3, GameConfig::GameConfig game_config)
    : world(new b2World(gravity)), vscreen(0, 0, 0, 0, 0.0f), 
      player{CreateTrigu(world, 0.1, 0.15, 0.1, 0.3, 1.0f, 0.3f, graphics::Color {0, 0, 255, 255})},
      velocity_iterations(velocity_iterations), position_iterations(position_iterations), game_config(game_config) {

    vscreen.width = 480;
    vscreen.height = 320;
    vscreen.offset_y = 0;
    #ifdef __PSVITA__
    vscreen.scale = SCREEN_HEIGHT / vscreen.height;
    vscreen.offset_x = (SCREEN_WIDTH - vscreen.width * vscreen.scale) / 2;
    #else
    // NOTE: 3DS has to handle offset in between screens
    vscreen.scale = 1.0f;
    vscreen.offset_x = 40;
    #endif


    players.emplace_back(player);
    register_object(player);

    TitleScreen* title_screen = new TitleScreen();
    screen_manager.add_screen(ScreenName::TITLE, title_screen);
    screen_manager.set_current_screen(ScreenName::TITLE);

    SettingsScreen* settings_screen = new SettingsScreen();
    screen_manager.add_screen(ScreenName::SETTINGS, settings_screen);
    
    ScreenTransition title_to_settings = ScreenTransition(title_screen, settings_screen, [](Screen* scr1, Screen* scr2){return true;});
    ScreenTransition settings_to_title = ScreenTransition(settings_screen, title_screen, [](Screen* scr1, Screen* scr2){return true;});

    screen_manager.add_transition(title_to_settings);
    screen_manager.add_transition(settings_to_title);
    
}

Trigu* Game::create_trigu(float x, float y, float w, float h, float density, float friction, const graphics::Color& color){
    return register_object(CreateTrigu(world, x, y, w, h, density, friction, color));
}

PolygonalObject* Game::create_polygonal_object(const b2Vec2* vertices, int vertices_count, float density, float friction, const graphics::Color& color, bool filled){
    return register_object(CreatePolygonalObject(world, vertices, vertices_count, density, friction, color, filled));
}

template<Derived<Object> T>
T* Game::register_object(const T& object) {
    objects.emplace_back(std::make_shared<T>(object));
    return (T*)(objects[objects.size()-1].get());
}

void Game::update(float dt) {
    //auto vel = player.body->GetLinearVelocity();
    //player.body->SetLinearVelocity();

    if (game_config.movement_mode == GameConfig::MovementMode::THRUST_AND_BRAKES) {
            float speed = 0.0;
            if (game_config.input_compatibility > GameConfig::InputCompatibility::DS) {
                player_speed += input::joystick1.y * (game_config.speed / 128.0f);
            } else {
                if (input::is_key_pressed(input::BUTTON_DPAD_DOWN)) {
                    speed += -game_config.speed;
                } else if (input::is_key_pressed(input::BUTTON_DPAD_UP)) {
                    speed += game_config.speed;
                }
            }

            if (player_speed > game_config.top_speed || player_speed < -game_config.top_speed) {
                player_speed = (player_speed / abs(player_speed)) * game_config.top_speed;
                // Don't
            } else {
                b2Vec2 force = b2Vec2(sin(player.body->GetAngle()) * player_speed, -cos(player.body->GetAngle()) * player_speed);
                player.body->SetLinearVelocity(force);
            }
            //float new_speed = (force + player.body->GetLinearVelocity()).Length();
       // TODO
    } else if (game_config.movement_mode == GameConfig::MovementMode::JOYSTICK2_STRAFE) {
        if (game_config.input_compatibility <= GameConfig::InputCompatibility::PSP) {
            graphics::text::draw_text(10, 30, "! Joystick2 strafe is not possible in PSP compatibility mode or below", 30, {255, 0, 0, 255});
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


    if (player_rotation_speed < game_config.rotation_top_speed && player_rotation_speed > -game_config.rotation_top_speed) {
        player.body->SetAngularVelocity(player_rotation_speed);
    } else {
        player_rotation_speed = (player_rotation_speed / abs(player_rotation_speed)) * game_config.rotation_top_speed;
    }

    world->Step(dt, velocity_iterations, position_iterations);

    // for (float fx = -1.5f * scale; fx < 1.5f * scale; fx+= 0.1f) {
    //     for (float fy = -1.0f * scale; fy < 1.0f * scale; fy += 0.1f) {
    //         graphics::draw_rectangle(vscreen.translate_x(fx * scale), vscreen.translate_y(fy * scale), 0.05f * scale * vscreen.scale, 0.05f * scale * vscreen.scale, graphics::Color {100, 100, 100});
    //     }
    // }
    //scale_t += dt;
    //if (scale != target_scale) {
    if (scale_grow_direction < 0.0f && scale <= target_scale) {
        scale = target_scale;
        scale_grow_direction = 0.0f;
    } else if (scale_grow_direction > 0.0f && scale >= target_scale) {
        scale = target_scale;
        scale_grow_direction = 0.0f;
    }

    // v = (x - x0) / t
    scale += dt * scale_grow_direction * ( abs(scale - target_scale) / (scale_grow_duration) );
    //}


    graphics::text::draw_text(30, 30, std::to_string(objects.size()).append("objs"));
    graphics::text::draw_text(30, 60, std::to_string(scale).append("scale"));

    //screen_manager.get_current_screen()->update();

    graphics::draw_line(0, 35, 200, 35, graphics::Color::BLUE());


    if (input::is_key_pressed(input::Buttons::BUTTON_CONFIRM)) {
// CreateTrigu(world, 20, 20, 20, 40, 1.0f, 0.3f, graphics::Color graphics::Color::BLUE())
        auto obj = this->create_trigu(20, 20, 20, 40, 0.1f, 0.3f, graphics::Color::BLUE());
        const auto pos = player.body->GetPosition();
        obj->body->SetTransform({pos.x, pos.y}, obj->body->GetAngle());
        
    }    

    for(auto& obj : objects) {
        obj->update();

        #ifdef __3DS__
        obj->draw(vscreen, true, scale);
        #else
        obj->draw(vscreen, false, scale);
        #endif

    }


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

    float scale_min_x = -(vscreen.width / 2) / min_x;
    float scale_max_x = (vscreen.width / 2) / max_x;
    float scale_min_y = -(vscreen.height / 2) / min_y;
    float scale_max_y = (vscreen.height / 2) / max_y;

    float scale_x = 0;
    float scale_y = 0;

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

    if (scale_x < scale_y) {
        target_scale = scale_x;
    } else {
        target_scale = scale_y;
    };
    if (scale > target_scale) {
        scale_grow_direction = -1.0;
    } else if (scale < target_scale) {
        scale_grow_direction = 1.0;
    } else {
        return;
    }

}

Game::~Game(){
    delete world;
}
