#include "game_screen.hpp"
#include "title_screen.hpp"
#include "settings_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "input.hpp"

void GameScreen::update(float dt) {

    game->update(dt / 1000);
    game->adjust_scale();

    graphics::text::draw_text(30, 30, std::to_string(this->game->objects.size()).append("objs"));
    graphics::text::draw_text(30, 60, std::to_string(this->game->scale).append("scale"));

    graphics::draw_line(0, 35, 200, 35, graphics::Color::BLUE());

    if (input::is_key_pressed(input::Buttons::BUTTON_START)) {
        ScreenManager::get_instance().transition_to(ScreenName::PAUSE);
    }
}
