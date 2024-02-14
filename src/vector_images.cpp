#include "vector_images.hpp"
#include "draw.hpp"
#include "screen.hpp"
#include "virtual_screen.hpp"

void vsc_draw_triangle(VirtualScreen vscreen, int x1, int y1, int x2, int y2, int x3, int y3, graphics::Color color) {
    graphics::draw_triangle(
        vscreen.offset_x + x1 * vscreen.scale_w,
        vscreen.offset_y + y1 * vscreen.scale_h,
        vscreen.offset_x + x2 * vscreen.scale_w,
        vscreen.offset_y + y2 * vscreen.scale_h,
        vscreen.offset_x + x3 * vscreen.scale_w,
        vscreen.offset_y + y3 * vscreen.scale_h,
        color
    );
}

int vsc_xadj(VirtualScreen vscreen, int x) {
    return vscreen.offset_x + x * vscreen.scale_w;
}
int vsc_yadj(VirtualScreen vscreen, int y) {
    return vscreen.offset_y + y * vscreen.scale_h;
}

namespace VectorImages {
    VectorImage ship_standard_acceleration {
        .w = 100,
        .h = 100,
        .image_render = [](VirtualScreen vscreen)->void{
            vsc_draw_triangle(vscreen, 10, 80, 50, 10, 90, 80, graphics::Color::WHITE());

            // Triangulito de la izquierda
            vsc_draw_triangle(vscreen, 25, 30, 25, 40, 40, 35, graphics::Color::YELLOW());

            // Triangulito de la derecha
            vsc_draw_triangle(vscreen, 65, 35, 80, 25, 80, 40, graphics::Color::YELLOW());

            // Triangulito de abajo
            vsc_draw_triangle(vscreen, 45, 95, 50, 85, 55, 95, graphics::Color::YELLOW());
        }
    };
}
