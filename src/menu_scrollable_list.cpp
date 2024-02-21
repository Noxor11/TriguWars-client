#include "menu_scrollable_list.hpp"
#include "draw.hpp"
#include "menu_draw.hpp"
#include "screen.hpp"
#include "text.hpp"
#include "virtual_screen.hpp"
#include <cmath>

ScrollableList::ScrollableList(
    const std::vector<std::shared_ptr<Widget>> &widgets, VirtualScreen vscreen)
    : vscreen(vscreen), widgets(widgets) {
        calculate_sizes();
        #if __PSVITA__
            graphics::text::reload_font();
        #endif
}

void ScrollableList::calculate_sizes() {
    this->widgets_size.clear();
    this->widgets_acum_size.clear();

    for (int i = 0; i < (int)this->widgets.size(); i++) {
        if (i < 1) {
            widgets_acum_size.push_back(0);
        }
        if (widgets[i]->height < 1) {
            if (widgets[i]->option->type == MenuOption::OptionType::RICH_ITERABLE) {
                widgets_size.push_back(graphics::text::pt_to_px(widgets[i]->fontsize_pt) * 2);
            } else {
                widgets_size.push_back(graphics::text::pt_to_px(widgets[i]->fontsize_pt));
            }
        } else {
            widgets_size.push_back(widgets[i]->height);
        }
        widgets_acum_size.push_back(
            widgets_acum_size[i] + widgets_size[i]
        );
    }
}

// TODO Implement VirtualScreen scaling
// TODO Take into account option margins for scroll calculations

void ScrollableList::render(float dt, int selection) {
    #ifdef __3DS__
    graphics::set_screen(graphics::TOP1);
    #endif

    dt_counter += dt;

    #define SCROLLBAR_WIDTH 0.05

    int index_start = 0;
    int offset = 0;
    if ((widgets_acum_size[selection] + widgets_size[selection]) > vscreen.height * 0.8) {
        for (int i = 0; i < widgets_size.size(); i++) {
            offset += widgets_size[i];
            index_start++;
            if ((widgets_acum_size[selection] + widgets_size[selection]) - offset < vscreen.height * 0.8) break;
        }
    }



    for (int i = index_start; i < (int)this->widgets.size(); i++) {
        auto woption = widgets[i]->option;

        float y0 = vscreen.offset_y +
            ((option_margin_top + option_margin_bottom) * i) + widgets_acum_size[i]
            + option_margin_top - offset;


        float y1 = y0 + widgets_size[i] + option_margin_bottom;

        if (y1 - vscreen.offset_y > vscreen.height) {
            break;
        }

        auto label = woption->name;

        if (selection == i) {
            graphics::draw_rectangle(vscreen.offset_x, y0, vscreen.width - (vscreen.width * SCROLLBAR_WIDTH), y1-y0, {
                50, 50, static_cast<int>((175.0f + (75.0f * sin(std::fmod(dt_counter, 2000.0f) / 2000 * 3.14)))), 255 }
            );
        }

        graphics::text::draw_text(vscreen.offset_x, y1, label, graphics::text::pt_to_size(widgets[i]->fontsize_pt),
                                  false, (selection == i) ? graphics::Color::WHITE() : graphics::Color::WHITE());

        float option_component_start = (vscreen.width) * 0.60 - (vscreen.width * SCROLLBAR_WIDTH) + vscreen.offset_x;
        float option_component_end = (vscreen.width) * 0.95  - (vscreen.width * SCROLLBAR_WIDTH) + vscreen.offset_x;

        if (woption->type == MenuOption::OptionType::ITERABLE) {
            auto option = std::static_pointer_cast<IterableMenuOption>(woption);
            draw_iterable_option(option.get(), option_component_start, y0, option_component_end, y1, widgets[i]->fontsize_pt);
        } else if (woption->type == MenuOption::OptionType::RANGE) {
            auto option = std::static_pointer_cast<RangeMenuOption>(woption);
            draw_range_option(option.get(), option_component_start, y0, option_component_end, y1, widgets[i]->fontsize_pt);
        } else if (woption->type == MenuOption::OptionType::RICH_ITERABLE) {
            auto option = std::static_pointer_cast<RichIterableOption>(woption);
            draw_rich_iterable_option_background(option.get(), option_component_start, y0, option_component_end, y1, graphics::Color::RED());
            draw_rich_iterable_option(option.get(), option_component_start, y0, option_component_end, y1, widgets[i]->fontsize_pt/2);
        }

        // FIXME Not PPI aware
    }

    int total_height = (widgets_acum_size.back() + widgets_size.back()) * 1.2;
    int scroll_start = float(offset) / total_height * vscreen.height;
    int scroll_end = (offset + vscreen.height) / total_height * vscreen.height;
    //if (scroll_end > vscreen.height) scroll_end = vscreen.height;
    graphics::draw_rectangle(vscreen.offset_x + vscreen.width * (1 - SCROLLBAR_WIDTH), vscreen.offset_y, vscreen.width * SCROLLBAR_WIDTH, vscreen.height, graphics::Color{255, 255, 255, 63});
    graphics::draw_rectangle(vscreen.offset_x + vscreen.width * (1 - SCROLLBAR_WIDTH), vscreen.offset_y + scroll_start, vscreen.width * SCROLLBAR_WIDTH, scroll_end - scroll_start, graphics::Color{255, 255, 255, 128});

}
