#pragma once

struct Color {
    int r;
    int g;
    int b;
    int a;
};

// Initialize graphics backend
void graphics_init();

// Run before closing program to free graphics and end graphics backend
void graphics_close();

// Run before starting to draw a frame
void start_frame();

// Run when frame is finished drawing to flip screen
void end_frame();

void draw_rectangle(int x, int y, int w, int h, Color color);
void draw_line(int x1, int y1, int x2, int y2, Color color);
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, Color color);
