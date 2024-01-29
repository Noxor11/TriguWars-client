#include "pause_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "input.hpp"
#include "screen_transitions.hpp"

#include <memory>
#include <vector>

using namespace graphics;
using namespace text;

MenuOption::MenuOption(const std::string& name, OptionType type) 
    : name(name), type(type) {}

ScreenWithMenu::ScreenWithMenu(const std::vector<std::shared_ptr<MenuOption>>& options)
    : options(options), selected_option_index(0) {
       
    };

ScreenWithMenu::ScreenWithMenu(const VirtualScreen &vscreen, const std::vector<std::shared_ptr<MenuOption>>& options) 
    : Screen(vscreen), options(options), selected_option_index(0) {

    };

ScreenWithMenu::~ScreenWithMenu() {}

void ScreenWithMenu::handle_menu() {
    Color color;
    for (unsigned int y = 90 * vscreen.scale, x = 20 * vscreen.scale, i = 0; i < options.size(); y += pt_to_px(30), ++i){

        if (options[i]->name == options[selected_option_index]->name)
            color = Color::RED();
        else
            color = Color::WHITE();

        draw_text(vscreen.translate_x(x), vscreen.translate_y(y), options[i]->name, pt_to_size(30), false, color);

        if (options[i]->type == MenuOption::OptionType::ITERABLE) {
            IterableMenuOption* iterable_option = (IterableMenuOption*)(options[i].get());
            const std::string& value = iterable_option->values[iterable_option->selected_value_index];
            draw_text(vscreen.translate_x(x + 200 * vscreen.scale), vscreen.translate_y(y), std::string("( ").append(value).append(" )"), 30, false, color);
        }

    }

    if (input::is_key_pressed(input::Buttons::BUTTON_DPAD_DOWN)) {
        ++selected_option_index;
        selected_option_index %= options.size();
    } else if (input::is_key_pressed(input::Buttons::BUTTON_DPAD_UP)) {
        --selected_option_index;
        selected_option_index %= options.size();
    }
    

    if (options[selected_option_index]->type == MenuOption::OptionType::ITERABLE) {
        IterableMenuOption* iterable_option = ((IterableMenuOption*)(options[selected_option_index].get()));
    
        if (input::is_key_pressed(input::Buttons::BUTTON_DPAD_RIGHT)) {
            iterable_option->selected_value_index++;
            iterable_option->selected_value_index %= iterable_option->values.size();
        } else if (input::is_key_pressed(input::Buttons::BUTTON_DPAD_LEFT)) {
            iterable_option->selected_value_index--;
            iterable_option->selected_value_index %= iterable_option->values.size();
        } 
    
    } 
    
    if (options[selected_option_index]->type == MenuOption::OptionType::ACTIONABLE) {
        ActionableMenuOption* actionable_option = ((ActionableMenuOption*)(options[selected_option_index].get()));
    
        if (input::is_key_pressed(input::Buttons::BUTTON_CONFIRM)) {
            actionable_option->on_action();
        } 
    }
}
