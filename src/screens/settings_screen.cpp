#include "settings_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "dimensions.hpp"
#include "input.hpp"
#include "screen_transitions.hpp"

using namespace graphics;
using namespace text;

static const std::vector<std::string> values ({"On", "Off"});

SettingsScreen::SettingsScreen() 
    : ScreenWithMenu(
        {
            IterableMenuOption::create("Invert X axis", values), 
            IterableMenuOption::create("Invert Y axis", values)
        }) {
}

void SettingsScreen::update(float dt){

    #ifdef __3DS__
    const float title_x = TOP_WIDTH_CENTER;
    const float title_y = 70;
    #elif defined __PSVITA__
    const float title_x = WIDTH_CENTER;
    const float title_y = 70;
    #endif


    graphics::text::draw_text(this->vscreen.translate_x(title_x), this->vscreen.translate_y(title_y), "Settings");

    if (input::is_key_pressed(input::Buttons::BUTTON_CANCEL)) {
        ScreenManager::get_instance().transition_to_last_screen();
    }

    this->handle_menu();
}
