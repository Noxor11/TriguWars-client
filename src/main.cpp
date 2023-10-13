#include "draw.hpp"

int main() {
    graphics_init();

    while (true) {
        start_frame();

        draw_rectangle(30, 30, 50, 50, Color {255, 0, 0, 255});
        draw_triangle(100, 100, 100, 200, 150, 150, {0, 0, 255, 255});

        end_frame();
    }

    graphics_close();
    return 0;
}
