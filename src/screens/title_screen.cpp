#include "virtual_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "screen.hpp"
#include "title_screen.hpp"

void TitleScreen::update() {
    // Debug
    graphics::draw_rectangle(vscreen.offset_x, vscreen.offset_y, vscreen.translate_w(vscreen.width), vscreen.translate_h(vscreen.height), {75, 75, 75, 255});

    // Para saber cómo cada librería renderiza el texto

    // Start of text
    graphics::draw_line(this->vscreen.translate_x(240/2), 0, this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2), {0, 255, 0, 255});

    // Baseline
    graphics::draw_line(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2), this->vscreen.translate_x(240/2)+30*9, this->vscreen.translate_y(320/2), {0, 0, 255, 255});

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2),
                        {255,255,255,255}, "TriguWars", 2);

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320 * 0.75f),
                        {255,255,255,255}, "Press X or A to continue");
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
