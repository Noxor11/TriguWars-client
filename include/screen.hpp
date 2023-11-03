#pragma once
#include "virtual_screen.hpp"
#include "dimensions.hpp"

#include <iostream>
#include <vector>
#include <functional>
#include <memory>

enum class ScreenName {
    TITLE,
    PAUSE,
    SETTINGS,
    OFFLINE_GAME,
    ONLINE_GAME
};


class Screen {
    protected: VirtualScreen vscreen;

    public:
        virtual void update() = 0;
        Screen() : vscreen(TITLESCREEN_VSCREEN_OFFSET_X, 0, 320, 240, TITLESCREEN_VSCREEN_SCALE) {};
        Screen(const VirtualScreen &vscreen): vscreen{vscreen} {};
        virtual ~Screen() = default;
};


struct MenuOption {
    struct OptionType {
        bool ACTIONABLE : 1; 
        bool ITERABLE: 1;
    };
    
    const std::string name;
    OptionType type = {0,0};
};

struct ActionableMenuOption : public MenuOption {
    ActionableMenuOption(const std::string name, std::function<void(void)> callback) 
        : MenuOption{name, OptionType{1, 0}}, on_action(callback) {}

    std::function<void()> on_action;
};

struct IterableMenuOption : public MenuOption {
    IterableMenuOption(const std::string name, const std::vector<std::string> values) 
        : MenuOption{name, OptionType{0, 1}}, values(values), selected_value_index{0} {}

    const std::vector<std::string> values;
    int selected_value_index;
};

class ScreenWithMenu : public Screen {
    
private:
    std::vector<MenuOption*> options;
    int selected_option_index;
    
public:

    ScreenWithMenu(std::vector<MenuOption*> options);
    ScreenWithMenu(const VirtualScreen &vscreen, std::vector<MenuOption*> options);
    void handle_menu();
};