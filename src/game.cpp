#include "game.hpp"
#include "draw.hpp"

Game::Game(const b2Vec2 &gravity, int velocity_iterations = 8, int position_iterations = 3)
    : world(b2World(gravity)), vscreen(VirtualScreen(0, 0, 0, 0, 0.0f)), velocity_iterations(velocity_iterations), position_iterations(position_iterations) {
    vscreen.width = 480;
    vscreen.height = 320;
    vscreen.offset_y = 0;
    #ifdef __PSVITA__
    vscreen.offset_x = (966 - 480 * 1.7f) / 2;
    #else
    // NOTE: 3DS has to handle offset in between screens
    vscreen.offset_x = 0;
    #endif

    #ifdef __PSVITA__
    // 544 / 320 = 1,7
    vscreen.scale = 1.7f;
    #else
    vscreen.scale = 1.0f;
    #endif
}

void Game::update(float dt) {
    world.Step(dt, velocity_iterations, position_iterations);
    // render
    for (b2Body* b = world.GetBodyList(); b; b = b->GetNext()) {
        for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {
            if ( f->GetType() == b2Shape::e_polygon) {
                b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
                graphics::Vector2 vertices[shape->m_count];
                for (int i = 0; i < shape->m_count; i++) {
                    vertices[i] = {shape->m_vertices[i].x, shape->m_vertices[i].y};
                }
                // FIXME: No hay colores, no se adapta a la pantalla ni na'
                graphics::draw_vertices(vertices, shape->m_count, graphics::Color {255, 0, 0, 255});
            }
        }
    }

}
