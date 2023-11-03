#include "pause_screen.hpp"
#include "draw.hpp"
#include "text.hpp"
#include "input.hpp"
#include "screen_transitions.hpp"

#include <memory>
#include <vector>

using namespace graphics;
using namespace text;

ScreenWithMenu::ScreenWithMenu(std::vector<MenuOption*> options)
    : options(options), selected_option_index(0) {
       
    };

ScreenWithMenu::ScreenWithMenu(const VirtualScreen &vscreen, std::vector<MenuOption*> options) 
    : Screen(vscreen), options(options), selected_option_index(0) {

    };

void ScreenWithMenu::handle_menu() {
    Color color;
    for (int y = 90, x = 20, i = 0; i < options.size(); y += 30, ++i){

        if (options[i]->name == options[selected_option_index]->name)
            color = Color::RED();
        else
            color = Color::WHITE();

        draw_text(x, y, options[i]->name, 30, color);
        

        if (options[i]->type.ITERABLE) {
            IterableMenuOption* iterable_option = (IterableMenuOption*)(&options[i]);
            const std::string& value = iterable_option->values[iterable_option->selected_value_index];
            draw_text(x + 200, y, std::string("(").append(value).append(")"), 30, color);
        }

    }

    if (input::is_key_pressed(input::Buttons::BUTTON_DPAD_DOWN)) {
        ++selected_option_index;
        selected_option_index %= options.size();
    } else if (input::is_key_pressed(input::Buttons::BUTTON_DPAD_UP)) {
        --selected_option_index;
        selected_option_index %= options.size();
    }
    
    draw_text(100,240, std::to_string(selected_option_index));

    if (options[selected_option_index]->type.ITERABLE) {
        IterableMenuOption* iterable_option = ((IterableMenuOption*)(&options[selected_option_index]));
    
        if (input::is_key_pressed(input::Buttons::BUTTON_DPAD_RIGHT)) {
            iterable_option->selected_value_index++;
            iterable_option->selected_value_index %= iterable_option->values.size();
        } else if (input::is_key_pressed(input::Buttons::BUTTON_DPAD_LEFT)) {
            iterable_option->selected_value_index--;
            iterable_option->selected_value_index %= iterable_option->values.size();
        } 
    
    } 
    
    if (options[selected_option_index]->type.ACTIONABLE){
        // ActionableMenuOption* actionable_option = ((ActionableMenuOption*)(options[selected_option_index].get()));
    
        // if (input::is_key_pressed(input::Buttons::BUTTON_CONFIRM)) {
        //     // actionable_option->on_action();
        // } 
    }
}
