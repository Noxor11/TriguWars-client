#include "draw.hpp"
#include "input.hpp"
#include "virtual_screen.hpp"
#include "trigu.hpp"
#include "title_screen.hpp"
#include <cmath>
#ifdef __3DS__
#include <3ds.h>
#endif

#include <iostream>
#include <string>

using namespace graphics;

int main() {

    graphics::init();
    input::init();
    VirtualScreen screen = VirtualScreen(0, 0, 100, 100, 1.0);
    TitleScreen title_screen;
    title_screen.init();
    Trigu trigito = Trigu(80, 80, 30, 30, 1/8 * 3.14, Color{0, 255, 255, 255});

    float i = 0;
    float x = 0.0;

#ifdef __3DS__
    while (aptMainLoop()) {
#else
    while (true) {
#endif
        trigito.rotation += 0.1;

        graphics::start_frame();

        input::scan();
        i += 3.14 / 60;
        if (input::is_key_down(input::BUTTON_DPAD_RIGHT)) {
            x += 2;
        }

        title_screen.update();

        graphics::draw_rectangle(30, 30, 50, 50, Color{255, 0, 0, 255});
        graphics::draw_triangle(100, 100, 100, 200, 150, 150, Color{0, 0, 255, 255});


        //screen.offset_x = std::cos(i) * 200 + 300;
        //screen.scale = std::cos(i) + 1.5;


        // VirtualScreen demo
        graphics::draw_rectangle(screen.offset_x, screen.offset_y,
                                 screen.width * screen.scale, screen.height * screen.scale, Color{255, 255, 255, 255});

        trigito.x += input::joystick1.x / 32;
        trigito.y -= input::joystick1.y / 32;

        trigito.render(screen);

        if (input::get_touch()) {
            graphics::draw_rectangle(input::touch.x, input::touch.y, 40, 40, {225, 192, 203, 255});
        }

        graphics::draw_rectangle(
            screen.translate_x(x), screen.translate_y(0), screen.translate_w(40), screen.translate_h(40), Color{0, 255, 0, 255}
        );

        graphics::end_frame();
    }

    graphics::close();
    return 0;
}
