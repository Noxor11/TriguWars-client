#include "virtual_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "screen.hpp"
#include "title_screen.hpp"
#include <cmath>

// Sí, esto lo moveré luego y lo haré bien, esto es una prueba
//struct Text {
//    std::string texto;
//    unsigned int original_size;
//    float original_height; // computed in constructor
//    unsigned int adjusted_size;
//};
//
//Text texts[2] = {
//    {"TriguWars", 1, -1, 0}, {"Press X or A to continue", 1, -1, 0}
//};

void TitleScreen::update() {
    // Debug
    graphics::draw_rectangle(vscreen.offset_x, vscreen.offset_y, vscreen.translate_w(vscreen.width), vscreen.translate_h(vscreen.height), {75, 75, 75, 255});

    // Para saber cómo cada librería renderiza el texto

    // Start of text
    graphics::draw_line(this->vscreen.translate_x(240/2), 0, this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2), {0, 255, 0, 255});

    // Baseline
    graphics::draw_line(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2), this->vscreen.translate_x(240/2)+30*9, this->vscreen.translate_y(320/2), {0, 0, 255, 255});

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320/2),
                        {255,255,255,255}, "TriguWars", 2);//texts[0].adjusted_size);

    graphics::text::draw_text(this->vscreen.translate_x(240/2), this->vscreen.translate_y(320 * 0.75f),
                        {255,255,255,255}, "Press X or A to continue", 30);

    graphics::text::draw_text(30, 200, {255,255,255,255}, std::to_string(texts[0].adjusted_size).c_str(), 30);
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
    for (int i = 0; i < 2; i++) {
        texts[i].original_height = graphics::text::measure_height(texts[i].texto, texts[i].original_size);

        float height = -1;
        float prev_height = -1;
        float target_height = vscreen.scale * texts[i].original_height;
        int final_size = 1;

        for (int i = 1; i < 999; i++) {
            prev_height = height;
            height = graphics::text::measure_height(texts[i].texto, i);

            if (i > 1 && height > target_height && prev_height < target_height) { final_size = i-1; break; }

            if (i > 1 && height > target_height) { final_size = i-1; break; }
            if (height == std::round(target_height)) { final_size = i; break; }

        }

        texts[i].adjusted_size = final_size;
    }
}
