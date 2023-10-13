#ifdef __PSVITA__

#include "../../../include/draw.hpp"

#include <vita2d.h>
#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

inline unsigned int Color::to_RGBA32() const {
    return RGBA8(this->r, this->g, this->b, this->a);
}

void graphics::init() {
    vita2d_init();
    vita2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0xFF));
}

void graphics::close() {
    vita2d_fini();
}

void graphics::start_frame() {
    vita2d_start_drawing();
    vita2d_clear_screen();
}

void graphics::end_frame() {
    vita2d_end_drawing();
    vita2d_swap_buffers();
}

void graphics::draw_rectangle(int x, int y, int w, int h, const Color& color) {
    vita2d_draw_rectangle(x, y, w, h, color.to_RGBA32());
}

void graphics::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color) {
    vita2d_color_vertex *vertices = (vita2d_color_vertex *)vita2d_pool_memalign(
                3 * sizeof(vita2d_color_vertex),
                sizeof(vita2d_color_vertex));


    vertices[0] = {(float)x1, (float)y1, 0, color.to_RGBA32()};
    vertices[1] = {(float)x2, (float)y2, 0, color.to_RGBA32()};
    vertices[2] = {(float)x3, (float)y3, 0, color.to_RGBA32()};
    vita2d_draw_array(SCE_GXM_PRIMITIVE_TRIANGLE_STRIP, vertices, 3);

}

#endif
