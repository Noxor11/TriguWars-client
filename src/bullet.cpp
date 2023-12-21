#include "bullet.hpp"
#include "trigu.hpp"
#include "game.hpp"
#include <box2d/box2d.h>
#include <iostream>

Bullet CreateBullet(b2World* world, float x, float y, float radius, int resolution, b2Vec2 direction, float speed, float density, float friction, const graphics::Color& color) {
    b2Vec2 vertices[resolution];

    for (int i = 0; i < resolution; i++) {
        float degree = 2 * 3.14 * (float(i) / resolution);
        vertices[i].Set(
            cos(degree) * radius,
            sin(degree) * radius
        );
    }

    b2CircleShape shape;
    shape.m_radius = radius;
    shape.m_p.Set(0, 0);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    b2Body* body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    fixtureDef.density = density;
    fixtureDef.friction = friction;

    body->CreateFixture(&fixtureDef);

    return Bullet(world, vertices, resolution, body, direction, speed, color);
}

void Bullet::handle_game_logic(float dt, Game *game) {
    for (auto player : game->players) {
        if ( b2TestOverlap(this->body->GetFixtureList()->GetAABB(0), player->body->GetFixtureList()->GetAABB(0)) ) {
           // Player hit
        }
    }

    for (auto object : game->objects) {
        if (object.get() == this) continue;
        if ( b2TestOverlap(this->body->GetFixtureList()->GetAABB(0), object->body->GetFixtureList()->GetAABB(0)) ) {
            for (int i = 0; i < game->players.size(); i++) {
                if (object.get() == game->players[i]) {
                    // Object is player
                        object->color = graphics::Color::GREEN();

                    if (object.get() == game->player) {
                       // Object is controlling player!!
                    } else {
                        // Object is other player. Can kill :)

                        game->players[i]->kill();
                    }

                }
            }

            // Object touched
            // Bullet has to die :(

            //auto iter = std::find_if(game->objects.begin(), game->objects.end(),
            //    [&](auto &o){ return (o.get() == this); }
            //);

            for (auto it = game->objects.begin(); it != game->objects.end();)
            {
                if (it->get() == this)
                    it = game->objects.erase(it);
                else
                    ++it;
            }

            for (auto it = game->bullets.begin(); it != game->bullets.end();)
            {
                if (*it.base() == this)
                    it = game->bullets.erase(it);
                else
                    ++it;
            }

            this->color = graphics::Color::GREEN();
            world->DestroyBody(this->body);

            // FIXME: No se elimina por completo, memory leak
            //delete this;
            break;
        }
    }
}
