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

// NOTE: Possibly add options for fit width or fit height
void draw_vector_image(const VectorImage* img, int x, int y, int w, int h) {
   VirtualScreen target_vsc = VirtualScreen(x, y, w, h, 1.0f);
   // By default draw_vector_image will stretch the image if requested w/h doesn't match the VectorImage aspect ratio
   // we achieve this by setting the w_scale and h_scale of VirtualScreen in relation to the VectorImage's and requested width and height
   target_vsc.scale_h = h / (float)img->h;
   target_vsc.scale_w = w / (float)img->w;

   img->image_render(target_vsc);
}

void draw_rich_item(const RichItem* richitem, int x, int y, int w, int h, int fontsize_pt) {
    int label_height = graphics::text::pt_to_px(fontsize_pt);
    int image_height = h - label_height;

    draw_vector_image(&richitem->image, x, y, w, image_height);
    graphics::text::draw_text(x, y + h, richitem->label,
                              graphics::text::pt_to_size(fontsize_pt), false);
}

void draw_rich_iterable_option_background(const RichIterableOption* option, float x0, float y0, float x1, float y1, graphics::Color color) {
    int w_item = (x1 - x0) / option->items.size();
    graphics::draw_rectangle(x0 + w_item * option->selected_value_index, y0, w_item, y1 - y0, color);
}

void draw_rich_iterable_option(const RichIterableOption* option, float x0, float y0, float x1, float y1, int fontsize_pt) {
    int w_item = (x1 - x0) / option->items.size();
    for (int i = 0; i < option->items.size(); i++) {
        draw_rich_item(&option->items[i], x0 + w_item * i, y0, w_item, y1 - y0, fontsize_pt);
    }
    // TODO: Provide function for button prompt rendering
    //graphics::text::draw_text(margin_left, vscreen.height + SETTINGSLIKESCREEN_OPTION_FONTSIZE * 0.20, "Left: Change value  Right: Change Value",
    //                            graphics::text::px_to_size(vscreen.height * SETTINGSLIKESCREEN_FOOTER_HEIGHT * 0.40));
}
