#pragma once
#include "virtual_screen.hpp"
#include "dimensions.hpp"

#include <iostream>
#include <vector>
#include <list>
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
        virtual void update(float dt = 0.0f) = 0;
        Screen() : vscreen(TITLESCREEN_VSCREEN_OFFSET_X, 0, 320, 240, TITLESCREEN_VSCREEN_SCALE) {};
        Screen(const VirtualScreen &vscreen): vscreen{vscreen} {};
        virtual ~Screen() = default;
};


struct MenuOption {
    struct OptionType {
        bool ACTIONABLE: 1; 
        bool ITERABLE: 1;
    };
protected:
    MenuOption(const std::string& name, OptionType type);
public:

    
    const std::string name;
    OptionType type = {0,0};
};

struct ActionableMenuOption : public MenuOption {
private:
    ActionableMenuOption(const std::string name, std::function<void(void)> callback) 
        : MenuOption{name, OptionType{1, 0}}, on_action(callback) {}

public:
    std::function<void()> on_action;
    
    // method that makes sure the object is always dynamically allocated
    static std::shared_ptr<ActionableMenuOption> create(const std::string& name, std::function<void(void)> callback) { return std::make_shared<ActionableMenuOption>(ActionableMenuOption(name, callback));};
};

struct IterableMenuOption : public MenuOption {
private:
    IterableMenuOption(const std::string name, const std::vector<std::string> values) 
        : MenuOption{name, OptionType{0, 1}}, values(values), selected_value_index{0} {}

public:
    const std::vector<std::string> values;
    int selected_value_index;

    // method that makes sure the object is always dynamically allocated
    static std::shared_ptr<IterableMenuOption> create(const std::string& name, const std::vector<std::string>& values) { return std::make_shared<IterableMenuOption>(IterableMenuOption(name, values)); };
};

class ScreenWithMenu : public Screen {
    
private:
    std::vector<std::shared_ptr<MenuOption>> options;
    int selected_option_index;
    
public:

    ScreenWithMenu(const std::vector<std::shared_ptr<MenuOption>>& options);
    ScreenWithMenu(const VirtualScreen &vscreen, const std::vector<std::shared_ptr<MenuOption>>& options);
    ~ScreenWithMenu();
    void handle_menu();
};
