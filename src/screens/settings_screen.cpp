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
            new IterableMenuOption("Invert X axis", values), 
            new IterableMenuOption("Invert Y axis", values)
        }) {
}

void SettingsScreen::update(){

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(140/2), "Settings");

    if (input::is_key_pressed(input::Buttons::BUTTON_CANCEL)) {
        ScreenManager::get_instance().transition_to_last_screen();
    }

    this->handle_menu();
}