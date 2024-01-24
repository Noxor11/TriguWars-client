#include "menu_draw.hpp"
#include "draw.hpp"
#include "text.hpp"
#include <sstream>

void draw_iterable_option(const IterableMenuOption* option, float x0, float y0, float x1, float y1, int fontsize_pt) {
    std::stringstream str;
    if (option->selected_value_index > 0) {
        //graphics::text::draw_text((vscreen.width - margin_right - margin_left) * 0.75 - margin_left - vscreen.width * 0.05, y1,
        //                          "(", graphics::text::pt_to_size(SETTINGSLIKESCREEN_OPTION_FONTSIZE), false, graphics::Color::WHITE());
        float origin_x = x0 + (x1 - x0) * 0.05;
        graphics::draw_triangle(origin_x, y0, x0, y0 + (y1-y0)/2, origin_x, y1, graphics::Color::WHITE());
    }

    str << option->values[option->selected_value_index];
    if (option->selected_value_index < (int)option->values.size() - 1) {
        //str << " )";
        float origin_x = x0 + (x1 - x0) * 0.95;
        graphics::draw_triangle(origin_x, y0, origin_x + (x1-x0) * 0.05, y0 + (y1-y0)/2, origin_x, y1, graphics::Color::WHITE());
    }

    float center_offset = graphics::text::get_text_width(str.str(), graphics::text::pt_to_size(fontsize_pt)) / 2;
    graphics::text::draw_text(x0 + ((x1 - x0)/2 - center_offset), y1,
                                str.str(), graphics::text::pt_to_size(fontsize_pt), false, graphics::Color::WHITE());

    // TODO: Provide function for button prompt rendering
    //graphics::text::draw_text(margin_left, vscreen.height + SETTINGSLIKESCREEN_OPTION_FONTSIZE * 0.20, "Left: Change value  Right: Change Value",
    //                            graphics::text::px_to_size(vscreen.height * SETTINGSLIKESCREEN_FOOTER_HEIGHT * 0.40));
}
void draw_range_option(const RangeMenuOption* option, float x0, float y0, float x1, float y1, int fontsize_pt) {
    std::stringstream str;
    str << option->current_value;

    //if (option->current_value > option->max_value) {
    //    //graphics::text::draw_text((vscreen.width - margin_right - margin_left) * 0.75 - margin_left - vscreen.width * 0.05, y1,
    //    //                          "(", graphics::text::pt_to_size(SETTINGSLIKESCREEN_OPTION_FONTSIZE), false, graphics::Color::WHITE());
    //    float origin_x = (vscreen.width - margin_right - margin_left) * 0.60 + margin_left;
    //    graphics::draw_triangle(origin_x, y0, origin_x-vscreen.width * 0.05, y0 + (y1-y0)/2, origin_x, y1, graphics::Color::WHITE());
    //}
    graphics::draw_line(x0, y0 + (y1 - y0)/2, x1, y0 + (y1-y0)/2, graphics::Color::WHITE());

    float progress = (option->current_value - option->min_value) / (option->max_value - option->min_value);
    float progress_start = x0 + (x1 - x0) * progress;

    graphics::draw_line(progress_start, y0, progress_start, y1, graphics::Color::WHITE());
    //if (option->current_value < option->min_value) {
    //    //str << " )";
    //    float origin_x = (vscreen.width - margin_right - margin_left) * 0.90 + margin_left;
    //    graphics::draw_triangle(origin_x, y0, origin_x+vscreen.width * 0.05, y0 + (y1-y0)/2, origin_x, y1, graphics::Color::WHITE());
    //}

    float center_offset = graphics::text::get_text_width(str.str(), graphics::text::pt_to_size(fontsize_pt)) / 2;
    graphics::text::draw_text(x0 + ((x1 - x0) / 2 - center_offset), y1,
                                str.str(), graphics::text::pt_to_size(fontsize_pt), false, graphics::Color::WHITE());

}
