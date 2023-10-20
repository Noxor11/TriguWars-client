#include "connected_line_object.hpp"
#include <box2d/box2d.h>



ConnectedLineObject::ConnectedLineObject(b2World* world, b2Vec2* vertices, int vertices_count, float density, float friction, const graphics::Color& color) :
    PolygonalObject(world, body, vertices, vertices_count, color) {

    b2PolygonShape shape;
    shape.Set(vertices, vertices_count);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(100, 100);

    b2Body* body = world->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    fixtureDef.density = density;
    fixtureDef.friction = friction;

    body->CreateFixture(&fixtureDef);

}

void ConnectedLineObject::draw(const VirtualScreen &vscreen, bool rotate) {
    int screen = 0; // 0 = upper, 1 = lower, 2 = both
    
    int i = 0;
    const auto position = body->GetPosition(); 
    for (i; i < this->vertices_count - 1; ++i) {
        graphics::draw_line(vertices[i].x + position.x, vertices[i].y + position.y, vertices[i+1].x + position.x, vertices[i+1].y + position.y, color);
    }

    graphics::draw_line(vertices[i].x + position.x, vertices[i].y + position.y, vertices[0].x + position.x, vertices[0].y + position.y, color);

}
