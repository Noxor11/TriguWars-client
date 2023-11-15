#include "player.hpp"
#include "trigu.hpp"
#include "game_config.hpp"
#include "input.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "polygonal_object.hpp"

void Player::update(float dt) {
    //auto vel = player.body->GetLinearVelocity();
    //player.body->SetLinearVelocity();

    graphics::text::draw_text(160, 60, std::string("move! ").append(std::to_string(speed)));
    if (is_dead) {
        respawn_accumulator += dt;
        if (respawn_accumulator > game_config->respawn_time) {
            body->SetEnabled(true);
            respawn_accumulator = 0.0f;
            is_dead = false;

            switch (game_config->respawn_method) {
                case GameConfig::RespawnMethod::CENTER:
                    body->SetTransform({10, 10}, 0);
                    break;
                case GameConfig::RespawnMethod::EQUDISTANT:
                    break;
                case GameConfig::RespawnMethod::RANDOM:
                    break;
            }

        }
        // No procesar el input si está muerto
        return;
    }

    if (game_config->movement_mode == GameConfig::MovementMode::THRUST_AND_BRAKES) {
        if (game_config->input_compatibility > GameConfig::InputCompatibility::DS) {
            speed += input::joystick1.y * (game_config->speed / 128.0f);
        } else {
            if (input::is_key_pressed(input::BUTTON_DPAD_DOWN)) {
                speed += -game_config->speed;
            } else if (input::is_key_pressed(input::BUTTON_DPAD_UP)) {
                speed += game_config->speed;
            }
        }

        b2Vec2 force = b2Vec2(sin(body->GetAngle()) * speed, -cos(body->GetAngle()) * speed);
        body->SetLinearVelocity(force);

    } else if (game_config->movement_mode == GameConfig::MovementMode::JOYSTICK2_STRAFE) {
        // TODO
        if (game_config->input_compatibility <= GameConfig::InputCompatibility::PSP) {
            graphics::text::draw_text(10, 30, "! Joystick2 strafe is not possible in PSP compatibility mode or below", 30, false, graphics::Color::RED());
        }
    } else {
        graphics::text::draw_text(10, 30, "!!!");
        // TODO
    }


    if (game_config->input_compatibility > GameConfig::InputCompatibility::DS) {
        rot_speed += input::joystick1.x * (game_config->rotation_speed / 128.0f);
    } else {
        if (input::is_key_pressed(input::BUTTON_DPAD_DOWN)) {
            rot_speed += -game_config->rotation_speed;
        } else if (input::is_key_pressed(input::BUTTON_DPAD_UP)) {
            rot_speed += game_config->rotation_speed;
        }
    }


    //if (player_rotation_speed < game_config.rotation_top_speed && player_rotation_speed > -game_config.rotation_top_speed) {
    body->SetAngularVelocity(rot_speed);
    //} else {
    //    player_rotation_speed = (player_rotation_speed / abs(player_rotation_speed)) * game_config.rotation_top_speed;
    //}
}

void Player::kill() {
    body->SetTransform({0, 0}, 0);
    body->SetLinearVelocity({0,0});
    body->SetAngularVelocity(0);
    speed = 0.0f;
    rot_speed = 0.0f;
    is_dead = true;
    respawn_accumulator = 0.0f;
    body->SetEnabled(false);
}

void Player::draw(const VirtualScreen &vscreen, bool rotate, float scale) {
    if (!is_dead) {
        // NOTE: Es posible que falle por cosas de cpp
        PolygonalObject::draw(vscreen, rotate, scale);
    }
}

Player CreateTriguPlayer(b2World* world, float x, float y, float w, float h, float density, float friction, const graphics::Color& color, GameConfig::GameConfig* game_config) {
    return Player(
        CreateTrigu(world, x, y, w, h, density, friction, color),
        game_config);
}
