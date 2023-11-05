#include "virtual_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "screen.hpp"
#include "pause_screen.hpp"
#include "screen_transitions.hpp"
#include "input.hpp"

using namespace graphics;
using namespace text;


PauseScreen::PauseScreen() 
    : ScreenWithMenu(
        {
            new ActionableMenuOption("Continue", [](){
                ScreenManager::get_instance().transition_to(ScreenName::OFFLINE_GAME);
            }), 
            new ActionableMenuOption("Settings", [](){
                ScreenManager::get_instance().transition_to(ScreenName::SETTINGS);
            }),
        }) {
}

void PauseScreen::update(float dt) {
    // Para saber cómo cada librería renderiza el texto

    #ifdef __3DS__
    set_screen(graphics::Screen::TOP1);
    draw_text(TOP_WIDTH_CENTER, TOP_HEIGHT_CENTER, "Pause");
    set_screen(graphics::Screen::BOTTOM);
    #elif defined __PSVITA__
        draw_text(WIDTH_CENTER, HEIGHT_CENTER, "Pause");
    #endif
    this->handle_menu();

    if (input::is_key_pressed(input::Buttons::BUTTON_CANCEL) || input::is_key_pressed(input::Buttons::BUTTON_START)) {
        ScreenManager::get_instance().transition_to_last_screen();
    }

}
