#include "settings_screen.hpp"
#include "draw.hpp"
#include "ppi_manager.hpp"
#include "text.hpp"
#include "dimensions.hpp"
#include "input.hpp"
#include "screen_transitions.hpp"
#include "vector_images.hpp"
#include <vector>

using namespace graphics;
using namespace text;

static const std::vector<std::string> values ({"On", "Off"});

SettingsScreen::SettingsScreen() 
    : SettingsLikeScreen (
        {
            IterableMenuOption::create("Invert Y axis", {"true", "false"}),
            IterableMenuOption::create("Compatibility mode", {"FULL", "PSVITA/3DS", "PSP", "GBA", "GB"}),
            RangeMenuOption::create("text scale", 0.5, 2.0, 0.25, float(get_ppi()) / DEFAULT_PPI),
            RichIterableOption::create("Example RichIterableOption", {
                    RichItem {
                        .label = "Nave A",
                        .image = VectorImages::ship_standard_acceleration
                    },
                    RichItem {
                        .label = "Nave B",
                        .image = VectorImages::ship_standard_acceleration
                    },
                    RichItem {
                        .label = "Nave C",
                        .image = VectorImages::ship_standard_acceleration
                    },
            })
        },
        "Settings",
        [this]() {
            auto item = std::find_if(this->options.begin(), this->options.end(), [&](std::shared_ptr<MenuOption> option){return option->name == "text scale";});
            auto option = std::static_pointer_cast<RangeMenuOption>(*item);
            set_ppi(option->current_value * DEFAULT_PPI);
            calculate_sizes();
            ScreenManager::get_instance().transition_to_last_screen();
            // Callback al confirmar
        }
        ) {}
