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

    return *new Bullet(world, vertices, resolution, body, direction, speed, color);
}

void Bullet::handle_game_logic(float dt, Game *game) {
    dt_acum += dt;
    // if (dt > 1000.0) {
    //     //kill(game);
    // }

    int deadly_contacts = 0;
    for (auto object : game->objects) {
        if (object.get() == this) continue;
        if (object.get() == game->player) continue;
        if ( b2TestOverlap(this->body->GetFixtureList()->GetAABB(0), object->body->GetFixtureList()->GetAABB(0)) ) {
            deadly_contacts++;
            for (int i = 0; i < game->players.size(); i++) {
                if (object.get() == game->players[i]) {
                    // Object is player
                        object->color = graphics::Color::GREEN();

                    if (object.get() == game->player) {
                       // Object is controlling player!!
                       deadly_contacts--;
                    } else {
                        // Object is other player

                        // Player is dead, ignore
                        if (((Player*)object.get())->is_dead) {
                            deadly_contacts--;
                            continue;
                        }

                        // Player is alive, can kill :)
                        game->players[i]->kill();
                    }

                }
            }

            // Object touched
            // Bullet has to die :(

            //auto iter = std::find_if(game->objects.begin(), game->objects.end(),
            //    [&](auto &o){ return (o.get() == this); }
            //);


            if (deadly_contacts > 0) {
                game->queue_bullet_deletion(this);
            }
            // FIXME: No se elimina por completo, memory leak
            //delete this;
            break;
        }
    }
}

void Bullet::kill(Game *game) {
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

    world->DestroyBody(this->body);
}

//Bullet::~Bullet() {
//    body->GetWorld()->DestroyBody(body);
//}
