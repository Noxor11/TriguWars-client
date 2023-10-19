#include "game.hpp"
#include "draw.hpp"
#include "trigu.hpp"

Game::Game(const b2Vec2 &gravity, int velocity_iterations = 8, int position_iterations = 3)
    : world(new b2World(gravity)), vscreen(VirtualScreen(0, 0, 0, 0, 0.0f)), player{CreateTrigu(this->world, 0, 0, 20, 40, 1.0f, 0.3f, graphics::Color {0, 0, 255, 255})}, velocity_iterations(velocity_iterations), position_iterations(position_iterations) {
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

    players.emplace_back(player);
    register_polygonal_object(player);
}


void Game::register_polygonal_object(const PolygonalObject& plobject) {
    polygonal_objects.emplace_back(PolygonalObject(plobject));
}
#include <iostream>
void Game::update(float dt) {
    world->Step(dt, velocity_iterations, position_iterations);

    for(auto& poly_obj : polygonal_objects) {
        graphics::Vector2 vertices[poly_obj.vertices_count];
        for (int i = 0; i < poly_obj.vertices_count; i++) {
            auto v = b2Mul(poly_obj.body->GetTransform(), poly_obj.vertices[i]);
            vertices[i] = {v.x, v.y};
        }
        std::cout << vertices[1].x << "\n";
        // graphics::draw_triangle(poly_obj.vertices[0].x, poly_obj.vertices[0].y, poly_obj.vertices[1].x, poly_obj.vertices[1].y, poly_obj.vertices[2].x, poly_obj.vertices[2].y, {255,0, 0, 255});
        graphics::draw_vertices(vertices, poly_obj.vertices_count, poly_obj.color);

    }


}

Game::~Game(){

}
