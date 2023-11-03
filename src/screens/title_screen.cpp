#include "virtual_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "screen.hpp"
#include "title_screen.hpp"
#include "screen_transitions.hpp"
#include "input.hpp"

void TitleScreen::update() {

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2), "TriguWars", 20);

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320 * 0.75f),"Press X or A to continue");

    if (input::is_key_pressed(input::Buttons::BUTTON_CONFIRM)) {
        ScreenManager::get_instance().transition_to(ScreenName::OFFLINE_GAME);
    }

    if (input::is_key_pressed(input::Buttons::BUTTON_START)) {
        ScreenManager::get_instance().transition_to(ScreenName::SETTINGS);
    }
}
