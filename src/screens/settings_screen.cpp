#include "settings_screen.hpp"
#include "draw.hpp"
#include "ppi_manager.hpp"
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
            IterableMenuOption::create("Coso1", {"A", "B", "C", "D"}),
            IterableMenuOption::create("Invert Y axis", {"1", "2", "3", "4"}),
            IterableMenuOption::create("Compatibility mode", {"FULL", "PSVITA/3DS", "PSP", "GBA", "GB"}),
            RangeMenuOption::create("text scale", 0.5, 2.0, 0.25, float(get_ppi()) / DEFAULT_PPI),
        }, "Settings",
        [this]() {
            auto option = std::static_pointer_cast<RangeMenuOption>(options[3]);
            set_ppi(option->current_value * DEFAULT_PPI);
            ScreenManager::get_instance().transition_to_last_screen();
            // Callback al confirmar
        }
        ) {}
