#pragma once
#include "screen.hpp"
#include "draw.hpp"

void draw_iterable_option(const IterableMenuOption* option, float x0, float y0, float x1, float y1, int fontsize_pt);
void draw_range_option(const RangeMenuOption* option, float x0, float y0, float x1, float y1, int fontsize_pt);
void draw_vector_image(const VectorImage* img, int x, int y, int w, int h);
void draw_rich_item(const RichItem* richitem, int x, int y, int w, int h, int fontsize_pt);
void draw_rich_iterable_option_background(const RichIterableOption* option, float x0, float y0, float x1, float y1, graphics::Color color);
void draw_rich_iterable_option(const RichIterableOption* option, float x0, float y0, float x1, float y1, int fontsize_pt);
