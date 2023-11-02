#include "virtual_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "screen.hpp"
#include "title_screen.hpp"
#include "screen_transitions.hpp"
#include "input.hpp"

void TitleScreen::update() const {
    // Debug
    graphics::draw_rectangle(vscreen.offset_x, vscreen.offset_y, vscreen.translate_w(vscreen.width), vscreen.translate_h(vscreen.height), {75, 75, 75, 255});

    // Para saber cómo cada librería renderiza el texto

    // Start of text
    graphics::draw_line(this->vscreen.translate_x(240/2), 0, this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2), graphics::Color::GREEN());

    // Baseline
    graphics::draw_line(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2), this->vscreen.translate_x(240/2)+30*9, this->vscreen.translate_y(320/2), graphics::Color::BLUE());

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2), "TriguWars", 20);

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320 * 0.75f),"Press X or A to continue");

    if (input::is_key_held(input::Buttons::BUTTON_START)) {
        ScreenManager::get_instance().transition_to(ScreenName::SETTINGS);
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

TitleScreen::TitleScreen(): Screen(VirtualScreen(TITLESCREEN_VSCREEN_OFFSET_X, 0, 320, 240, TITLESCREEN_VSCREEN_SCALE)) {
}
