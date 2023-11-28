#include "screen.hpp"
#include "draw.hpp"
#include "text.hpp"

SettingsLikeScreen::SettingsLikeScreen(const std::vector<std::shared_ptr<MenuOption>>& options, std::string header, std::function<void(void)> confirm_callback):
header(header), options(options), confirm_callback(confirm_callback) {
    this->margin_left = vscreen.width * SETTINGSLIKESCREEN_MARGIN_LEFT;
    this->margin_right = vscreen.width * SETTINGSLIKESCREEN_MARGIN_RIGHT;
    this->option_margin_top = vscreen.height * SETTINGSLIKESCREEN_OPTION_MARGIN_TOP;
    this->option_margin_bottom = vscreen.height * SETTINGSLIKESCREEN_OPTION_MARGIN_BOTTOM;

    this->option_total_height = SETTINGSLIKESCREEN_OPTION_HEIGHT + option_margin_top + option_margin_bottom;
}

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

    for (int i = 0; i < this->options.size(); i++) {
        float y0 = vscreen.height * SETTINGSLIKESCREEN_HEADER_HEIGHT + ((option_total_height + option_margin_top) * i) + option_margin_top;
        auto label = this->options[i]->name;
        graphics::text::draw_text(margin_left, y0+SETTINGSLIKESCREEN_OPTION_FONTSIZE, label, graphics::text::px_to_size(SETTINGSLIKESCREEN_OPTION_FONTSIZE));
        graphics::draw_line(margin_left, y0, margin_left, y0 + SETTINGSLIKESCREEN_OPTION_FONTSIZE, {255, i * 50, i * 50, 255});
    }
}

SettingsLikeScreen::~SettingsLikeScreen() {

}
