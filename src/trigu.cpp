#include "trigu.hpp"
#include <box2d/box2d.h>

Trigu CreateTrigu(b2World* world, float x, float y, float w, float h, float density, float friction, const graphics::Color& color) {
    b2Vec2 vertices[3];
    // NOTE: No cambiar el orden! Tiene que ser según las agujas del reloj
    vertices[0].Set(x+w / 2.0f, y);
    vertices[2].Set(x, y+h);
    vertices[1].Set(x+w, y+h);

    b2PolygonShape shape;
    shape.Set(vertices, 3);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    b2Body* body = world->CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    fixtureDef.density = density;
    fixtureDef.friction = friction;

    body->CreateFixture(&fixtureDef);

    return Trigu(world, vertices, 3, body, color);
}
