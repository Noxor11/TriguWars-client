#include "menu_draw.hpp"
#include "ppi_manager.hpp"
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

    for (int i = 0; i < (int)this->options.size(); i++) {
        float y0 = vscreen.height * SETTINGSLIKESCREEN_HEADER_HEIGHT + ((option_total_height + graphics::text::pt_to_px(SETTINGSLIKESCREEN_OPTION_FONTSIZE) + option_margin_top) * i) + option_margin_top;
        float y1 = y0 + pt_to_px(SETTINGSLIKESCREEN_OPTION_FONTSIZE);
        auto label = this->options[i]->name;

        if (selected_option_index == i) {
            graphics::draw_rectangle(margin_left, y0, vscreen.width - margin_right - margin_left, y1-y0, {
                50, 50, static_cast<int>((175.0f + (75.0f * sin(std::fmod(dt_counter, 2000.0f) / 2000 * 3.14)))), 255 }
            );
        }

        graphics::text::draw_text(margin_left, y1, label, graphics::text::pt_to_size(SETTINGSLIKESCREEN_OPTION_FONTSIZE),
                                  false, (selected_option_index == i) ? graphics::Color::WHITE() : graphics::Color::WHITE());

        float option_component_start = (vscreen.width - margin_right - margin_left) * 0.60 + margin_left;
        float option_component_end = (vscreen.width - margin_right - margin_left) * 0.90 + margin_left + vscreen.width * 0.05;

        if (options[i]->type.ITERABLE) {
            auto option = std::static_pointer_cast<IterableMenuOption>(options[i]);
            draw_iterable_option(option.get(), option_component_start, y0, option_component_end, y1, SETTINGSLIKESCREEN_OPTION_FONTSIZE);
            if (selected_option_index == i) {
                if (input::is_key_pressed(input::BUTTON_DPAD_LEFT) && option->selected_value_index > 0) {
                    option->selected_value_index--;
                } else if (input::is_key_pressed(input::BUTTON_DPAD_RIGHT) && option->selected_value_index < (int)option->values.size() - 1) {
                    option->selected_value_index++;
                }
            }
        } else if (options[i]->type.RANGE) {
            auto option = std::static_pointer_cast<RangeMenuOption>(options[i]);
            draw_range_option(option.get(), option_component_start, y0, option_component_end, y1, SETTINGSLIKESCREEN_OPTION_FONTSIZE);
            if (selected_option_index == i) {
                if (input::is_key_pressed(input::BUTTON_DPAD_LEFT) && option->current_value > option->min_value) {
                    option->current_value -= option->step;
                } else if (input::is_key_pressed(input::BUTTON_DPAD_RIGHT) && option->current_value < option->max_value) {
                    option->current_value += option->step;
                }
            }
        }

        // FIXME Not PPI aware
        graphics::draw_line(margin_left, y0, margin_left, y0 + SETTINGSLIKESCREEN_OPTION_FONTSIZE, {255, i * 50, i * 50, 255});
    }

    if (input::is_key_pressed(input::BUTTON_DPAD_DOWN) && selected_option_index < (int)options.size() - 1) {
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
