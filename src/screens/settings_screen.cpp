#include "virtual_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "screen.hpp"
#include "settings_screen.hpp"
#include "screen_transitions.hpp"
#include "input.hpp"

void SettingsScreen::update() const {
    // Para saber cómo cada librería renderiza el texto

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(140/2),
                        {255,255,255,255}, "Settings", 30);

    if (input::is_key_down(input::Buttons::BUTTON_CANCEL)) {
        ScreenManager::get_instance().transition_to(ScreenName::TITLE);
    }

}

#ifdef __PSVITA__
#define TITLESCREEN_VSCREEN_SCALE 2.26f
#elif defined __3DS__
#define TITLESCREEN_VSCREEN_SCALE 1.0f
#endif

#ifdef __PSVITA__
#define TITLESCREEN_VSCREEN_OFFSET_X 960 / 2 - (320 * 2.26f) / 2
#elif defined __3DS__
#define TITLESCREEN_VSCREEN_OFFSET_X 0
#endif

SettingsScreen::SettingsScreen(): Screen(VirtualScreen(TITLESCREEN_VSCREEN_OFFSET_X, 0, 320, 240, TITLESCREEN_VSCREEN_SCALE)) {
}
