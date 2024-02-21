#include "game_screen.hpp"
#include "screen_transitions.hpp"
#include "title_screen.hpp"
#include "settings_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "input.hpp"

void GameScreen::update(float dt) {

    game->update(dt / 1000);
    game->adjust_scale();

    if (input::is_key_pressed(input::Buttons::BUTTON_START)) {
        ScreenManager::get_instance().transition_to(ScreenName::PAUSE);
    }
}
