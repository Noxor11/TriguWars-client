#pragma once
#include <box2d/box2d.h>
#include "draw.hpp"
#include "polygonal_object.hpp"

class Game;

class Bullet : public PolygonalObject {
  float radius;
  b2Vec2 direction;
  float speed;

  public:
    Bullet(b2World* world, b2Vec2* vertices, unsigned int vertices_count, b2Body* body, b2Vec2 direction, float speed, const graphics::Color &color)
        : PolygonalObject(world, body, vertices, vertices_count, color), direction(direction), speed(speed) {
        body->SetLinearVelocity({direction.x * speed, direction.y * speed});
    };

    void handle_game_logic(float dt, Game *game);
};

Bullet CreateBullet(b2World* world, float x, float y, float radius, int resolution, b2Vec2 direction, float speed, float density, float friction, const graphics::Color& color);
