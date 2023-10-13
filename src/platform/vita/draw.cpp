#include "../../draw.hpp"

#include <vita2d.h>

void graphics_init() {
    vita2d_init();
    vita2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0xFF));
}

void graphics_close() {
    vita2d_fini();
}

void start_frame() {
    vita2d_start_drawing();
    vita2d_clear_screen();
}

void end_frame() {
    vita2d_end_drawing();
    vita2d_swap_buffers();
}

void draw_rectangle(int x, int y, int w, int h, Color color) {
    vita2d_draw_rectangle(x, y, w, h, RGBA8(color.r, color.g, color.b, color.a));
}
