#pragma once

#include "screen.hpp"

#include <unordered_map>
#include <string>
#include <functional>


/**
 * @brief Function used to transition between two screens
 * 
 * @returns true when transition finishes, false otherwise. 
*/
typedef std::function<bool(Screen* scr1, Screen* scr2)> ScreenTransitionFunction;

class ScreenTransition {
public:
    Screen* scr1;
    Screen* scr2;

    ScreenTransitionFunction fun;

    ScreenTransition(Screen* scr1, Screen* scr2, ScreenTransitionFunction function);
};


class ScreenManager {
private:
    std::unordered_map<ScreenName, Screen*> screens;
    std::vector<ScreenTransition> transitions;

    Screen* current_screen;
    ScreenManager();

public:
    ~ScreenManager();
    ScreenManager(ScreenManager const&)   = delete; 
    void operator=(ScreenManager const&)  = delete; // we don't want to be able to create another instance
    static ScreenManager& get_instance();
    
    Screen* get_current_screen();
    void set_current_screen(ScreenName name);
    Screen* get_screen_by_name(ScreenName name);
    void add_screen(ScreenName name, Screen* screen);
    void add_transition(const ScreenTransition& transition);

    /** @brief Transitions from the current screen to the one specified 
     * 
     * @returns true when transition finishes, false otherwise.
    */
    bool transition_to(ScreenName screen_name);
};
