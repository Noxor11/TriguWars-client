#include "settings_screen.hpp"
#include "draw.hpp"
#include "ppi_manager.hpp"
#include "settings_like_screen.hpp"
#include "text.hpp"
#include "dimensions.hpp"
#include "input.hpp"
#include "screen_transitions.hpp"
#include "vector_images.hpp"
#include <memory>
#include <vector>

using namespace graphics;
using namespace text;

static const std::vector<std::string> values ({"On", "Off"});

SettingsScreen::SettingsScreen()
    : SettingsLikeScreen (
        {
            std::make_shared<Widget>(Widget{
                .id = "Coso1",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE,
                .option = IterableMenuOption::create("Coso1", {"A", "B", "C", "D"})
            }),
            std::make_shared<Widget>(Widget {
                .id = "Invert Y axis",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE,
                .option = IterableMenuOption::create("Invert Y axis", {"1", "2", "3", "4"}),
            }),
            std::make_shared<Widget>(Widget {
                .id = "Compatibility mode",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE,
                .option = IterableMenuOption::create("Compatibility mode", {"FULL", "PSVITA/3DS", "PSP", "GBA", "GB"}),
            }),
            std::make_shared<Widget>(Widget {
                .id = "text scale",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE,
                .option = RangeMenuOption::create("text scale", 0.5, 2.0, 0.25, float(get_ppi()) / DEFAULT_PPI),
            }),
            std::make_shared<Widget>(Widget {
                .id = "Example RichIterableOption",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE,
                .option = RichIterableOption::create("Example RichIterableOption", {
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
            }),
            std::make_shared<Widget>(Widget {
                .id = "Widget Size 1",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE,
                .option = IterableMenuOption::create("Widget Size 1", {"Ejemplo"}),
            }),
            std::make_shared<Widget>(Widget {
                .id = "Widget Size 2",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE * 2,
                .option = IterableMenuOption::create("Widget Size 2", {"Ejemplo"}),
            }),
            std::make_shared<Widget>(Widget {
                .id = "Widget Size 3",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE * 3,
                .option = IterableMenuOption::create("Widget Size 3", {"Ejemplo"}),
            }),
            std::make_shared<Widget>(Widget {
                .id = "Widget Size 2B",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE,
                .option = IterableMenuOption::create("Widget Size 2B", {"Ejemplo"}),
            }),
            std::make_shared<Widget>(Widget {
                .id = "Widget Size 1B",
                .fontsize_pt = SETTINGSLIKESCREEN_OPTION_FONTSIZE,
                .option = IterableMenuOption::create("Widget Size 1B", {"Ejemplo"}),
            }),
        },
        "Settings",
        [this]() {
            auto option = (RangeMenuOption*)(&widgets[3]->option);
            set_ppi(option->current_value * DEFAULT_PPI);
            scrollable_list->calculate_sizes();
            ScreenManager::get_instance().transition_to_last_screen();
            // Callback al confirmar
        }
        ) {}
