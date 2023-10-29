#include "game.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "object.hpp"
#include "trigu.hpp"
#include "polygonal_object.hpp"
#include "dimensions.hpp"
#include "title_screen.hpp"
#include "input.hpp"
#include "settings_screen.hpp"

#include <memory>


Game::Game(const b2Vec2 &gravity, int velocity_iterations = 8, int position_iterations = 3)
    : world(new b2World(gravity)), vscreen(0, 0, 0, 0, 0.0f), 
      player{CreateTrigu(world, 20, 20, 20, 40, 1.0f, 0.3f, graphics::Color {0, 0, 255, 255})},
      velocity_iterations(velocity_iterations), position_iterations(position_iterations) {

    vscreen.width = 480;
    vscreen.height = 320;
    vscreen.offset_y = 0;
    #ifdef __PSVITA__
    vscreen.scale = SCREEN_HEIGHT / vscreen.height;
    vscreen.offset_x = (SCREEN_WIDTH - vscreen.width * vscreen.scale) / 2;
    #else
    // NOTE: 3DS has to handle offset in between screens
    vscreen.scale = 1.0f;
    vscreen.offset_x = 40;
    #endif


    players.emplace_back(player);
    register_object(player);

    TitleScreen* title_screen = new TitleScreen();
    screen_manager.add_screen(ScreenName::TITLE, title_screen);
    screen_manager.set_current_screen(ScreenName::TITLE);

    SettingsScreen* settings_screen = new SettingsScreen();
    screen_manager.add_screen(ScreenName::SETTINGS, settings_screen);
    
    ScreenTransition title_to_settings = ScreenTransition(title_screen, settings_screen, [](Screen* scr1, Screen* scr2){return true;});
    ScreenTransition settings_to_title = ScreenTransition(settings_screen, title_screen, [](Screen* scr1, Screen* scr2){return true;});

    screen_manager.add_transition(title_to_settings);
    screen_manager.add_transition(settings_to_title);
    
}

Trigu* Game::create_trigu(float x, float y, float w, float h, float density, float friction, const graphics::Color& color){
    return register_object(CreateTrigu(world, x, y, w, h, density, friction, color));
}

PolygonalObject* Game::create_polygonal_object(b2Vec2* vertices, int vertices_count, float density, float friction, const graphics::Color& color, bool filled){
    return register_object(CreatePolygonalObject(world, vertices, vertices_count, density, friction, color, filled));
}

template<Derived<Object> T>
T* Game::register_object(const T& object) {
    objects.emplace_back(std::make_shared<T>(object));
    return (T*)(objects[objects.size()-1].get());
}

void Game::update(float dt) {
    world->Step(dt, velocity_iterations, position_iterations);


    graphics::text::draw_text(30, 30, {255, 255, 255, 255}, std::to_string(objects.size()).append("objs"), 30);
    screen_manager.get_current_screen()->update();


    graphics::draw_line(0, 35, 200, 35, {0, 0, 255, 255});

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
    delete world;
}
