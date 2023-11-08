#pragma once

#include <box2d/box2d.h>
#include "polygonal_object.hpp"
#include "trigu.hpp"
#include "game_config.hpp"

class Player : public PolygonalObject {
    public:
        bool is_dead;
        float respawn_accumulator;
        float speed;
        float rot_speed;
        GameConfig::GameConfig* game_config;

        Player(b2World* const world, b2Body* const body, const b2Vec2* vertices, unsigned int vertices_count, const graphics::Color &color, GameConfig::GameConfig* game_config, bool filled = true):
            PolygonalObject(world, body, vertices, vertices_count, color, filled), 
            is_dead(false), respawn_accumulator(false), speed(0.0f), rot_speed(0.0f),
            game_config(game_config)  {};

        Player(const Trigu &trigu, GameConfig::GameConfig* game_config):
            PolygonalObject(trigu), is_dead(false), respawn_accumulator(false),
            speed(0.0f), rot_speed(0.0f), game_config(game_config) {};

        Player(const PolygonalObject &polygonal_object, GameConfig::GameConfig* game_config):
            PolygonalObject(polygonal_object), is_dead(false), respawn_accumulator(false),
            speed(0.0f), rot_speed(0.0f), game_config(game_config) {};

        void kill();
        void update(float dt) override;
        virtual void draw(const VirtualScreen &vscreen, bool rotate = false, float scale = 1.0) override;
};

Player CreateTriguPlayer(b2World* world, float x, float y, float w, float h, float density, float friction, const graphics::Color& color, GameConfig::GameConfig* game_config);
