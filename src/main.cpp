#include "draw.hpp"

int main() {
    Graphics::init();

    while (true) {
        Graphics::start_frame();

        Graphics::draw_rectangle(30, 30, 50, 50, Color{255, 0, 0, 255});
        Graphics::draw_triangle(100, 100, 100, 200, 150, 150, {0, 0, 255, 255});

        Graphics::end_frame();
    }

    Graphics::close();
    return 0;
}
