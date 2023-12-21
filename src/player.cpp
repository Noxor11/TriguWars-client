#include "player.hpp"
#include "trigu.hpp"
#include "game_config.hpp"
#include "input.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "polygonal_object.hpp"
#include "game.hpp"

void Player::update(float dt) {
    //auto vel = player.body->GetLinearVelocity();
    //player.body->SetLinearVelocity();

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
        return;
    }


    auto angle = b2Vec2(-sin(body->GetAngle()), cos(body->GetAngle()));
    if (game_config->movement_mode == GameConfig::MovementMode::THRUST_AND_BRAKES) {
        if (game_config->input_compatibility > GameConfig::InputCompatibility::DS) {
            if (input::joystick1.y != 0){
                b2Vec2 force = b2Vec2(angle.x * input::joystick1.y / 1E6, angle.y * input::joystick1.y / 1E6);
                body->ApplyLinearImpulseToCenter(force, true);
            }
        } else {
            if (input::is_key_pressed(input::BUTTON_DPAD_DOWN)) {
                b2Vec2 force = b2Vec2(angle.x * speed, angle.y * speed);
                body->ApplyLinearImpulseToCenter(force, true);

            } else if (input::is_key_pressed(input::BUTTON_DPAD_UP)) {
                b2Vec2 force = b2Vec2(angle.x * speed, angle.y * speed);
                body->ApplyLinearImpulseToCenter(force, true);
            }
        }


    } else if (game_config->movement_mode == GameConfig::MovementMode::JOYSTICK2_STRAFE) {
        // TODO
        if (game_config->input_compatibility <= GameConfig::InputCompatibility::PSP) {
            graphics::text::draw_text(10, 30, "! Joystick2 strafe is not possible in PSP compatibility mode or below", 30, false, graphics::Color::RED());
        }} else {graphics::text::draw_text(10, 30, "!!!");
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

void Player::handle_game_logic(float dt, Game* game) {
    if (input::is_key_pressed(input::BUTTON_AUX_LEFT)) {
        auto angle = b2Vec2(-sin(body->GetAngle()), cos(body->GetAngle()));
        auto pos = body->GetPosition();
        game->create_bullet(pos.x + angle.x * 0.2, pos.y + angle.y * 0.2, 0.025 , 16, {angle.x, angle.y}, 0.50, 10, 10, graphics::Color::RED(), true);
    }

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
        auto angle = b2Vec2(-sin(body->GetAngle()), cos(body->GetAngle()));
        graphics::draw_line(100, 100, 100 + angle.x * 50, 100 + angle.y * 50, graphics::Color::PURPLE());

        graphics::draw_line(
            vscreen.translate_x((body->GetPosition().x * scale + vscreen.width/2) * vscreen.scale),
            vscreen.translate_y((body->GetPosition().y * scale + vscreen.height/2) * vscreen.scale),
            vscreen.translate_x(((body->GetPosition().x + angle.x * 0.2) * scale + vscreen.width/2) * vscreen.scale),
            vscreen.translate_y(((body->GetPosition().y + angle.y * 0.2) * scale + vscreen.height/2) * vscreen.scale),
            graphics::Color::PURPLE()
        );

    } else {
        graphics::draw_rectangle(vscreen.offset_x, (vscreen.height - 20) * vscreen.scale,
                                 (respawn_accumulator / game_config->respawn_time) * vscreen.width * vscreen.scale, vscreen.height * vscreen.scale, graphics::Color(100, 100, 255, 255 * 0.7f));
    }
}

Player CreateTriguPlayer(b2World* world, float x, float y, float w, float h, float density, float friction, const graphics::Color& color, GameConfig::GameConfig* game_config) {
    return Player(
        CreateTrigu(world, x, y, w, h, density, friction, color),
        game_config);
}
