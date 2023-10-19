#include "game.hpp"
#include "draw.hpp"
#include "trigu.hpp"
#include <iostream>

Game::Game(const b2Vec2 &gravity, int velocity_iterations = 8, int position_iterations = 3)
    : world(new b2World(gravity)), vscreen(VirtualScreen(0, 0, 0, 0, 0.0f)), player{CreateTrigu(this->world, 20, 20, 20, 40, 1.0f, 0.3f, graphics::Color {0, 0, 255, 255})}, velocity_iterations(velocity_iterations), position_iterations(position_iterations) {
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
    register_object(player);
}

void Game::register_object(const Object &object) {
    objects.emplace_back(std::make_shared<Object>(object));
}

void Game::update(float dt) {
    world->Step(dt, velocity_iterations, position_iterations);

    for(auto& obj : objects) {
        obj->update();

        #ifdef __3DS__
        obj->draw(vscreen, true);
        #else
        obj->draw(vscreen, false);
        #endif

    }


}

Game::~Game(){

}
