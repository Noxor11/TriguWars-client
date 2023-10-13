#include "../include/draw.hpp"

int main() {
    graphics::init();

    while (true) {
        graphics::start_frame();

        graphics::draw_rectangle(30, 30, 50, 50, Color{255, 0, 0, 255});
        graphics::draw_triangle(100, 100, 100, 200, 150, 150, Color{0, 0, 255, 255});

        graphics::end_frame();
    }

    graphics::close();
    return 0;
}
