#include "virtual_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "screen.hpp"
#include "title_screen.hpp"
#include "screen_transitions.hpp"
#include "input.hpp"
#include "dimensions.hpp"

void TitleScreen::update(float dt) {

    #ifdef __3DS__
    const float title_x = TOP_WIDTH_CENTER;
    const float title_y = TOP_HEIGHT_CENTER;

    const float message_x = title_x;
    const float message_y = TOP_HEIGHT_CENTER + 30;
    #elif defined(__PSVITA__) || defined(__PC__)
    const float title_x = WIDTH_CENTER;
    const float title_y = HEIGHT_CENTER;

    const float message_x = title_x;
    const float message_y = HEIGHT_CENTER + 30;
    #endif

    graphics::text::draw_text(this->vscreen.translate_x(title_x), this->vscreen.translate_y(title_y), "TriguWars", 30, true);
    graphics::text::draw_text(this->vscreen.translate_x(message_x), this->vscreen.translate_y(message_y),"Press X or A to continue", 20, true);

    if (input::is_key_pressed(input::Buttons::BUTTON_CONFIRM)) {
        ScreenManager::get_instance().transition_to(ScreenName::OFFLINE_GAME);
    }

    if (input::is_key_pressed(input::Buttons::BUTTON_START)) {
        ScreenManager::get_instance().transition_to(ScreenName::SETTINGS);
    }
}
