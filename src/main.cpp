#include "../include/draw.hpp"
#include "virtual_screen.hpp"
#include <cmath>

int main() {

    VirtualScreen screen = VirtualScreen(0, 0, 100, 100, 1.0);

    graphics::init();

    float i = 0;
    float x = 0.0;

    while (true) {
        i += 3.14 / 60;
        x += 2;
        if (x > 60) x = 0;

        graphics::start_frame();

        graphics::draw_rectangle(30, 30, 50, 50, Color{255, 0, 0, 255});
        graphics::draw_triangle(100, 100, 100, 200, 150, 150, Color{0, 0, 255, 255});


        screen.offset_x = std::cos(i) * 200 + 300;
        //screen.scale = std::cos(i) + 1.5;

        // VirtualScreen demo
        graphics::draw_rectangle(screen.offset_x, screen.offset_y,
                                 screen.width * screen.scale, screen.height * screen.scale, Color{255, 255, 255, 255/2});

        graphics::draw_rectangle(
            screen.translate_x(x), screen.translate_y(0), screen.translate_w(40), screen.translate_h(40), Color{0, 255, 0, 255}
        );

        graphics::end_frame();
    }

    graphics::close();
    return 0;
}
