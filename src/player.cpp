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

    if (is_dead) {
        graphics::text::draw_text(160, 80, "Player is dead");
        //respawn_accumulator += dt;
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
        return;
    }


    if (game_config->movement_mode == GameConfig::MovementMode::THRUST_AND_BRAKES) {
        if (game_config->input_compatibility > GameConfig::InputCompatibility::DS) {
            if (input::joystick1.y != 0){
                b2Vec2 force = b2Vec2(sin(body->GetAngle()) * input::joystick1.y / 1'000'000, -cos(body->GetAngle()) * input::joystick1.y / 1'000'000);
                body->ApplyLinearImpulseToCenter(force, true);
            }
        } else {
            if (input::is_key_pressed(input::BUTTON_DPAD_DOWN)) {
                b2Vec2 force = b2Vec2(sin(body->GetAngle()) * speed, -cos(body->GetAngle()) * speed);
                body->ApplyLinearImpulseToCenter(force, true);

            } else if (input::is_key_pressed(input::BUTTON_DPAD_UP)) {
                b2Vec2 force = b2Vec2(sin(body->GetAngle()) * speed, -cos(body->GetAngle()) * speed);
                body->ApplyLinearImpulseToCenter(force, true);
            }
        }


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
        if (input::joystick1.x != 0){
            rot_speed = input::joystick1.x * (game_config->rotation_speed / 128.0f);
            body->ApplyAngularImpulse(rot_speed, true);
        }

    } else {
        if (input::is_key_pressed(input::BUTTON_DPAD_DOWN)) {
            body->ApplyAngularImpulse(rot_speed, true);

        } else if (input::is_key_pressed(input::BUTTON_DPAD_UP)) {
            body->ApplyAngularImpulse(rot_speed, true);
        }
    }


    //if (player_rotation_speed < game_config.rotation_top_speed && player_rotation_speed > -game_config.rotation_top_speed) {
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
    //body->SetEnabled(false);
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
