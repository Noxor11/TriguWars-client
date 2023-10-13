#pragma once
#include <cstdint>

struct Color {
    int r;
    int g;
    int b;
    int a;

    inline unsigned int to_RGBA32() const;
};

namespace graphics {

    // Initialize graphics backend
    void init();

    // Run before closing program to free graphics and end graphics backend
    void close();

    // Run before starting to draw a frame
    void start_frame();

    #ifdef __3DS__
    void set_screen();
    #endif

    // Run when frame is finished drawing to flip screen
    void end_frame();

    void draw_rectangle(int x, int y, int w, int h, Color const& color);
    void draw_line(int x1, int y1, int x2, int y2, Color const& color);
    void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, Color const& color);
}