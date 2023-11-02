#pragma once

#include <cstdint>
#include <string>

namespace graphics {

    #ifdef __3DS__
    enum Screen {
        TOP1, TOP2, BOTTOM
    };
    
    extern Screen selected_screen;
    #endif

    struct Color {
        int r = 0;
        int g = 0;
        int b = 0;
        int a = 255;

        static inline Color RED()      {return Color{255,0,0,255};};
        static inline Color GREEN()    {return Color{0,255,0,255};};
        static inline Color BLUE()     {return Color{0,0,255,255};};
        static inline Color WHITE()    {return Color{255,255,255,255};};
        static inline Color BLACK()    {return Color{0,0,0,255};};
        unsigned int to_RGBA32() const;
    };

    struct Vector2 {
        float x;
        float y;
    };
    
    // Initialize graphics backend
    void init();

    // Run before closing program to free graphics and end graphics backend
    void close();

    // Run before starting to draw a frame
    void start_frame();

    #ifdef __3DS__
    void set_screen(Screen scr);
    #endif

    // Run when frame is finished drawing to flip screen
    void end_frame();

    void draw_rectangle(int x, int y, int w, int h, const Color& color);
    void draw_line(int x1, int y1, int x2, int y2, const Color& color);
    void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color);
    void draw_vertices(const Vector2 *vertices, int n_vertices, const Color& color, bool fill = true);
}
