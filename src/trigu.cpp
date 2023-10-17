#include "trigu.hpp"
#include <box2d/box2d.h>

Trigu::Trigu(b2World world, float x, float y, float w, float h, float density, float friction, const graphics::Color& color) {
    b2Vec2 vertices[3];
    // NOTE: No cambiar el orden! Tiene que ser según las agujas del reloj
    vertices[0].Set(x+w / 2.0f, y);
    vertices[2].Set(x, y+h);
    vertices[1].Set(x+w, y+h);
    shape.Set(vertices, 3);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    body = world.CreateBody(&bodyDef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    fixtureDef.density = density;
    fixtureDef.friction = friction;
}
