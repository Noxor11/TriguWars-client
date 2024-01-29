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
        #ifdef __3DS__
        Screen() : vscreen(0, 0, TOP_SCREEN_WIDTH, SCREEN_HEIGHT, 1.0) {};
        #else
        Screen() : vscreen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1.0) {};
        #endif
        Screen(const VirtualScreen &vscreen): vscreen{vscreen} {};
        virtual ~Screen() = default;
};


struct MenuOption {
    enum class OptionType {
        UNDEFINED,
        ACTIONABLE,
        ITERABLE,
        RANGE
    };
protected:
    MenuOption(const std::string& name, OptionType type);
public:

    
    const std::string name;
    OptionType type = OptionType::UNDEFINED;
};

struct ActionableMenuOption : public MenuOption {
private:
    ActionableMenuOption(const std::string name, std::function<void(void)> callback) 
        : MenuOption{name, OptionType::ACTIONABLE}, on_action(callback) {}

public:
    std::function<void()> on_action;
    
    // method that makes sure the object is always dynamically allocated
    static std::shared_ptr<ActionableMenuOption> create(const std::string& name, std::function<void(void)> callback) { return std::make_shared<ActionableMenuOption>(ActionableMenuOption(name, callback));};
};

struct IterableMenuOption : public MenuOption {
private:
    IterableMenuOption(const std::string name, const std::vector<std::string> values) 
        : MenuOption{name, OptionType::ITERABLE}, values(values), selected_value_index{0} {}

public:
    const std::vector<std::string> values;
    int selected_value_index;

    // method that makes sure the object is always dynamically allocated
    static std::shared_ptr<IterableMenuOption> create(const std::string& name, const std::vector<std::string>& values) { return std::make_shared<IterableMenuOption>(IterableMenuOption(name, values)); };
};

struct RangeMenuOption : public MenuOption {
private:
    RangeMenuOption(const std::string name, const float min_value, const float max_value, const float step, const float default_value)
        : MenuOption{name, OptionType::RANGE}, min_value(min_value), max_value(max_value), step(step), current_value(default_value) {}

public:
    float min_value;
    float max_value;
    float step;
    float current_value;

    // method that makes sure the object is always dynamically allocated
    static std::shared_ptr<RangeMenuOption>
        create(const std::string name, const float min_value, const float max_value, const float step, const float default_value)
            { return std::make_shared<RangeMenuOption>(RangeMenuOption(name, min_value, max_value, step, default_value)); };
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

#define SETTINGSLIKESCREEN_MARGIN_LEFT 0.05
#define SETTINGSLIKESCREEN_MARGIN_RIGHT 0.05
#define SETTINGSLIKESCREEN_HEADER_HEIGHT 0.15
#define SETTINGSLIKESCREEN_FOOTER_HEIGHT 0.15
#define SLS SETTINGS_LIKE_SCREEN
#define SETTINGSLIKESCREEN_OPTION_FONTSIZE 19
#define SETTINGSLIKESCREEN_OPTION_MARGIN_TOP 0.005
#define SETTINGSLIKESCREEN_OPTION_MARGIN_BOTTOM 0.005


class SettingsLikeScreen : public Screen {
    public:
        std::string header;
        std::vector<std::shared_ptr<MenuOption>> options;
        std::function<void(void)> confirm_callback;
        int selected_option_index;
        float offset_y;
        float option_margin_top;
        float option_margin_bottom;
        float margin_left;
        float margin_right;
        float option_total_height;
        float dt_counter = 0;

        SettingsLikeScreen(const std::vector<std::shared_ptr<MenuOption>>& options, std::string header, std::function<void(void)> confirm_callback);
        ~SettingsLikeScreen();
        void update(float dt);
};
