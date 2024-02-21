#include "settings_like_screen.hpp"
#include "menu_scrollable_list.hpp"
#include "screen.hpp"
#include "menu_draw.hpp"
#include "ppi_manager.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "input.hpp"
#include "virtual_screen.hpp"
#include "widget.hpp"
#include <cmath>
#include <memory>
#include <sstream>

SettingsLikeScreen::SettingsLikeScreen(
    const std::vector<std::shared_ptr<Widget>> &widgets, std::string header,
    std::function<void(void)> confirm_callback)
    : header(header), widgets(widgets), confirm_callback(confirm_callback) {

    this->margin_left = vscreen.width * SETTINGSLIKESCREEN_MARGIN_LEFT;
    this->margin_right = vscreen.width * SETTINGSLIKESCREEN_MARGIN_RIGHT;
    this->option_margin_top =
      vscreen.height * SETTINGSLIKESCREEN_OPTION_MARGIN_TOP;
    this->option_margin_bottom =
      vscreen.height * SETTINGSLIKESCREEN_OPTION_MARGIN_BOTTOM;

    this->option_total_margin =
      option_margin_top + option_margin_bottom;
    this->scrollable_list = new ScrollableList(widgets,
      VirtualScreen(margin_left, vscreen.offset_y + SETTINGSLIKESCREEN_HEADER_HEIGHT * vscreen.height,
                    vscreen.width - margin_left - margin_right,
                    vscreen.height - (SETTINGSLIKESCREEN_HEADER_HEIGHT + SETTINGSLIKESCREEN_FOOTER_HEIGHT) * vscreen.height,
                    1.0f)
    );

    #if __PSVITA__
    graphics::text::reload_font();
    #endif
}

/*void SettingsLikeScreen::calculate_sizes() {
    this->options_size.clear();
    this->options_acum_size.clear();

    for (int i = 0; i < (int)this->options.size(); i++) {
        if (i < 1) {
            options_acum_size.push_back(0);
        }
        if (options[i]->type == MenuOption::OptionType::RICH_ITERABLE) {
            options_size.push_back(pt_to_px(SETTINGSLIKESCREEN_OPTION_FONTSIZE) * 2);
        } else {
            options_size.push_back(pt_to_px(SETTINGSLIKESCREEN_OPTION_FONTSIZE));
        }
        options_acum_size.push_back(
            options_acum_size[i] + options_size[i]
        );
    }
}
*/

void SettingsLikeScreen::update(float dt) {
    #ifdef __3DS__
    graphics::set_screen(graphics::TOP1);
    #endif

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

    if (input::is_key_pressed(input::BUTTON_DPAD_LEFT) || input::is_key_pressed(input::BUTTON_DPAD_RIGHT)) {
        auto woption = widgets[selected_option_index]->option;
        if (woption->type == MenuOption::OptionType::ITERABLE) {
            auto option = std::static_pointer_cast<IterableMenuOption>(woption);
            if (input::is_key_pressed(input::BUTTON_DPAD_LEFT) && option->selected_value_index > 0) {
                option->selected_value_index--;
            } else if (input::is_key_pressed(input::BUTTON_DPAD_RIGHT) && option->selected_value_index < (int)option->values.size() - 1) {
                option->selected_value_index++;
            }

        } else if (woption->type == MenuOption::OptionType::RANGE) {
            auto option = std::static_pointer_cast<RangeMenuOption>(woption);
            if (input::is_key_pressed(input::BUTTON_DPAD_LEFT) && option->current_value > option->min_value) {
                option->current_value -= option->step;
            } else if (input::is_key_pressed(input::BUTTON_DPAD_RIGHT) && option->current_value < option->max_value) {
                option->current_value += option->step;
            }

        } else if (woption->type == MenuOption::OptionType::RICH_ITERABLE) {
            auto option = std::static_pointer_cast<RichIterableOption>(woption);
            if (input::is_key_pressed(input::BUTTON_DPAD_LEFT) && option->selected_value_index > 0) {
                option->selected_value_index--;
            } else if (input::is_key_pressed(input::BUTTON_DPAD_RIGHT) && option->selected_value_index < (int)option->items.size() - 1) {
                option->selected_value_index++;
            }

        }

        // FIXME Not PPI aware
        //graphics::draw_line(margin_left, y0, margin_left, y0 + SETTINGSLIKESCREEN_OPTION_FONTSIZE, {255, i * 50, i * 50, 255});
    }

    if (input::is_key_pressed(input::BUTTON_DPAD_DOWN) && selected_option_index < (int)widgets.size() - 1) {
        selected_option_index ++;
    } else if (input::is_key_pressed(input::BUTTON_DPAD_UP) && selected_option_index > 0 ) {
        selected_option_index --;
    }

    if (input::is_key_pressed(input::BUTTON_START)) {
        this->confirm_callback();
    }

    scrollable_list->render(dt, selected_option_index);
}

SettingsLikeScreen::~SettingsLikeScreen() {

}
