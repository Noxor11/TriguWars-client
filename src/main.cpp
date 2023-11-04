#include "draw.hpp"
#include "game.hpp"
#include "text.hpp"
#include "input.hpp"
#include "virtual_screen.hpp"
#include "trigu.hpp"
#include "title_screen.hpp"
#include "object.hpp"
#include "text.hpp"
#include "settings_screen.hpp"
#include "pause_screen.hpp"
#include "game_screen.hpp"
#include "screen.hpp"
#include "pause_screen.hpp"
#ifdef __3DS__
#include <3ds.h>
#include <citro2d.h>
#endif

#include <box2d/box2d.h>
#include <cmath>
#include <string>

using namespace graphics;

int main() {
    graphics::init();
    graphics::text::set_font("CubicCoreMono");
    input::init();
    

    Game game = Game(b2Vec2(0.0f, 0.0f), 4, 2);

    b2Vec2 vertices[] = {{( 10 + 100 ) * (1.5 / 480), ( 20+ 100 ) * (1.0 / 320)},
                            {( 100 ) * (1.5 / 480), ( 20 + 100 ) * (1.0 / 320)},
                            {( -10+ 100 ) * (1.5 / 480), 100 * (1.0 / 320)},
                            {(100) * (1.5 / 480), ( -5 + 100 ) * (1.0 / 320)},
                            {(20 + 100) * (1.5 / 480), 100 * (1.0 / 320)}
                        };

    auto obj = game.create_polygonal_object(vertices, 5, 1,2, Color::WHITE(), false);
    obj->body->SetTransform({150 * (1.5 / 480), 200 * (1.0 / 320)}, 0);

    auto obj2 = game.create_polygonal_object(vertices, 5, 1,2, Color::WHITE(), false);
    obj2->body->SetTransform({40 * (1.5 / 480), 100 * (1.0 / 320)}, 0);
    game.adjust_scale();
    game.scale = game.target_scale;


    TitleScreen* title_screen = new TitleScreen();
    PauseScreen* pause_screen = new PauseScreen();
    SettingsScreen* settings_screen = new SettingsScreen();
    GameScreen* game_screen = new GameScreen(&game);

    ScreenManager& screen_manager = ScreenManager::get_instance();

    screen_manager.add_screen(ScreenName::TITLE, title_screen);
    screen_manager.add_screen(ScreenName::SETTINGS, settings_screen);
    screen_manager.add_screen(ScreenName::PAUSE, pause_screen);
    screen_manager.add_screen(ScreenName::OFFLINE_GAME, game_screen);
    screen_manager.set_current_screen(ScreenName::TITLE);
    
    ScreenTransition title_to_settings  = ScreenTransition(title_screen, settings_screen, [](::Screen* scr1, ::Screen* scr2){return true;});
    ScreenTransition title_to_game      = ScreenTransition(title_screen, game_screen,     [](::Screen* scr1, ::Screen* scr2){return true;});
    ScreenTransition settings_to_title  = ScreenTransition(settings_screen, title_screen, [](::Screen* scr1, ::Screen* scr2){return true;});
    ScreenTransition game_to_pause      = ScreenTransition(game_screen, pause_screen,     [](::Screen* scr1, ::Screen* scr2){return true;});
    ScreenTransition pause_to_game      = ScreenTransition(pause_screen, game_screen,     [](::Screen* scr1, ::Screen* scr2){return true;});

    screen_manager.add_transition(title_to_settings);
    screen_manager.add_transition(title_to_game);
    screen_manager.add_transition(settings_to_title);
    screen_manager.add_transition(game_to_pause);
    screen_manager.add_transition(pause_to_game);
    
#ifdef __3DS__
    while (aptMainLoop()) {
#else
    while (true) {
#endif
        
        graphics::start_frame();
        input::scan();

        screen_manager.get_current_screen()->update();
        graphics::draw_vertices((Vector2*)obj->vertices, 5, Color::WHITE());
        graphics::end_frame();
    }

    graphics::close();
    return 0;
}
