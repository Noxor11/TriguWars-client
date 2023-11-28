#include "settings_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "dimensions.hpp"
#include "input.hpp"
#include "screen_transitions.hpp"

using namespace graphics;
using namespace text;

static const std::vector<std::string> values ({"On", "Off"});

SettingsScreen::SettingsScreen() 
    : SettingsLikeScreen (
        {
            IterableMenuOption::create("Coso1", {"A", "B"}),
            IterableMenuOption::create("Invert Y axis", {"C", "D"})
        }, "Settings",
        []() {
            // Callback al confirmar
        }
        ) {}
