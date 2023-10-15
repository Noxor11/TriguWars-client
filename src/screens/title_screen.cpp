#include "virtual_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "screen.hpp"
#include "title_screen.hpp"

void TitleScreen::update() {
    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2),
                        {255,255,255,255}, "TriguWars", 30);

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320 * 0.75f),
                        {255,255,255,255}, "Press X or A to continue", 30);
}

void TitleScreen::init() {
}

#ifdef __PSVITA__
#define TITLESCREEN_VSCREEN_SCALE 1.7f
#elif defined __3DS__
#define TITLESCREEN_VSCREEN_SCALE 1.0f
#endif

TitleScreen::TitleScreen(): Screen(VirtualScreen(0, 0, 240, 320, TITLESCREEN_VSCREEN_SCALE)) {
}
