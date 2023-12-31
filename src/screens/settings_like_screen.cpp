#include "screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "input.hpp"
#include <cmath>
#include <sstream>

using graphics::text::pt_to_px;

SettingsLikeScreen::SettingsLikeScreen(
    const std::vector<std::shared_ptr<MenuOption>> &options, std::string header,
    std::function<void(void)> confirm_callback)
    : header(header), options(options), confirm_callback(confirm_callback) {
  this->margin_left = vscreen.width * SETTINGSLIKESCREEN_MARGIN_LEFT;
  this->margin_right = vscreen.width * SETTINGSLIKESCREEN_MARGIN_RIGHT;
  this->option_margin_top =
      vscreen.height * SETTINGSLIKESCREEN_OPTION_MARGIN_TOP;
  this->option_margin_bottom =
      vscreen.height * SETTINGSLIKESCREEN_OPTION_MARGIN_BOTTOM;

  this->option_total_height =
      graphics::text::pt_to_px(SETTINGSLIKESCREEN_OPTION_FONTSIZE) +
      option_margin_top + option_margin_bottom;
    #if __PSVITA__
    graphics::text::reload_font();
    #endif
}

void SettingsLikeScreen::update(float dt) {
    #ifdef __3DS__
    graphics::set_screen(graphics::TOP1);
    #endif

    dt_counter += dt;

    graphics::draw_line(0, vscreen.height * SETTINGSLIKESCREEN_HEADER_HEIGHT, vscreen.width, vscreen.height * SETTINGSLIKESCREEN_HEADER_HEIGHT, graphics::Color::RED());

    graphics::draw_line(vscreen.width  * SETTINGSLIKESCREEN_MARGIN_LEFT,
                        vscreen.height * SETTINGSLIKESCREEN_HEADER_HEIGHT,
                        vscreen.width  * SETTINGSLIKESCREEN_MARGIN_LEFT,
                        vscreen.height - vscreen.height * SETTINGSLIKESCREEN_FOOTER_HEIGHT,
                        graphics::Color::BLUE());

    graphics::draw_line(vscreen.width - vscreen.width  * SETTINGSLIKESCREEN_MARGIN_RIGHT,
                        vscreen.height * SETTINGSLIKESCREEN_HEADER_HEIGHT,
                        vscreen.width - vscreen.width  * SETTINGSLIKESCREEN_MARGIN_RIGHT,
                        vscreen.height - vscreen.height * SETTINGSLIKESCREEN_FOOTER_HEIGHT,
                        graphics::Color::YELLOW());

    graphics::draw_line(0, vscreen.height - vscreen.height * SETTINGSLIKESCREEN_FOOTER_HEIGHT, vscreen.width, vscreen.height - vscreen.height * SETTINGSLIKESCREEN_FOOTER_HEIGHT, graphics::Color::GREEN());

    for (int i = 0; i < this->options.size(); i++) {
        float y0 = vscreen.height * SETTINGSLIKESCREEN_HEADER_HEIGHT + ((option_total_height + option_margin_top) * i) + option_margin_top;
        float y1 = y0 + pt_to_px(SETTINGSLIKESCREEN_OPTION_FONTSIZE);
        auto label = this->options[i]->name;

        if (selected_option_index == i) {
            graphics::draw_rectangle(margin_left, y0, vscreen.width - margin_right - margin_left, y1-y0, {
                50, 50, static_cast<int>((175.0f + (75.0f * sin(std::fmod(dt_counter, 2000.0f) / 2000 * 3.14)))), 255 }
            );
        }

        graphics::text::draw_text(margin_left, y1, label, graphics::text::pt_to_size(SETTINGSLIKESCREEN_OPTION_FONTSIZE),
                                  false, (selected_option_index == i) ? graphics::Color::WHITE() : graphics::Color::WHITE());

        if (options[i]->type.ITERABLE) {
            auto option = std::static_pointer_cast<IterableMenuOption>(options[i]);
            std::stringstream str;
            if (option->selected_value_index > 0) {
                //graphics::text::draw_text((vscreen.width - margin_right - margin_left) * 0.75 - margin_left - vscreen.width * 0.05, y1,
                //                          "(", graphics::text::pt_to_size(SETTINGSLIKESCREEN_OPTION_FONTSIZE), false, graphics::Color::WHITE());
                float origin_x = (vscreen.width - margin_right - margin_left) * 0.60 + margin_left;
                graphics::draw_triangle(origin_x, y0, origin_x-vscreen.width * 0.05, y0 + (y1-y0)/2, origin_x, y1, graphics::Color::WHITE());
            }

            str << option->values[option->selected_value_index];
            if (option->selected_value_index < option->values.size() - 1) {
                //str << " )";
                float origin_x = (vscreen.width - margin_right - margin_left) * 0.90 + margin_left;
                graphics::draw_triangle(origin_x, y0, origin_x+vscreen.width * 0.05, y0 + (y1-y0)/2, origin_x, y1, graphics::Color::WHITE());
            }
            float center_offset = graphics::text::get_text_width(str.str(), graphics::text::pt_to_size(SETTINGSLIKESCREEN_OPTION_FONTSIZE)) / 2;
            graphics::text::draw_text((vscreen.width - margin_right - margin_left) * 0.75 - center_offset + margin_left, y1,
                                      str.str(), graphics::text::pt_to_size(SETTINGSLIKESCREEN_OPTION_FONTSIZE), false, graphics::Color::WHITE());

            graphics::text::draw_text(margin_left, vscreen.height + SETTINGSLIKESCREEN_OPTION_FONTSIZE * 0.20, "Left: Change value  Right: Change Value",
                                      graphics::text::px_to_size(vscreen.height * SETTINGSLIKESCREEN_FOOTER_HEIGHT * 0.40));

            if (selected_option_index == i) {
                if (input::is_key_pressed(input::BUTTON_DPAD_LEFT) && option->selected_value_index > 0) {
                    option->selected_value_index--;
                } else if (input::is_key_pressed(input::BUTTON_DPAD_RIGHT) && option->selected_value_index < option->values.size() - 1) {
                    option->selected_value_index++;
                }
            }
        }
        graphics::draw_line(margin_left, y0, margin_left, y0 + SETTINGSLIKESCREEN_OPTION_FONTSIZE, {255, i * 50, i * 50, 255});
    }

    if (input::is_key_pressed(input::BUTTON_DPAD_DOWN) && selected_option_index < options.size() - 1) {
        selected_option_index ++;
    } else if (input::is_key_pressed(input::BUTTON_DPAD_UP) && selected_option_index > 0 ) {
        selected_option_index --;
    }

    if (input::is_key_pressed(input::BUTTON_START)) {
        this->confirm_callback();
    }
}

SettingsLikeScreen::~SettingsLikeScreen() {

}
