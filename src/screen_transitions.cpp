#include "screen_transitions.hpp"


ScreenTransition::ScreenTransition(Screen* scr1, Screen* scr2, ScreenTransitionFunction function)
    : scr1(scr1), scr2(scr2), fun{function} {}


ScreenManager::ScreenManager() = default;

ScreenManager& ScreenManager::get_instance(){
    static ScreenManager instance; // Instantiated on first use.
    return instance;
}

ScreenManager::~ScreenManager(){
    for (auto pair : screens){
        delete pair.second; // deleting screens
    }
}

Screen* ScreenManager::get_current_screen(){
    return current_screen;
}

Screen* ScreenManager::get_last_screen(){
    return last_screen;
}

void ScreenManager::set_current_screen(ScreenName name){
    last_screen = current_screen;
    current_screen = get_screen_by_name(name);
}

Screen* ScreenManager::get_screen_by_name(ScreenName name) {
    return screens.at(name);
}

void ScreenManager::add_screen(ScreenName name, Screen* screen){
    screens.insert(std::make_pair(name, screen));
}

void ScreenManager::add_transition(const ScreenTransition& transition){
    transitions.emplace_back(transition);
}

#include <iostream>

bool ScreenManager::transition_to(ScreenName name){
    bool finished = true;
    
    for (auto& trans : transitions) {
        if (trans.scr1 == current_screen){
            finished = trans.fun(trans.scr1, trans.scr2);
        }
    }

    if (finished){
        last_screen = current_screen;   
        current_screen = get_screen_by_name(name);
    }
    
    return finished;
}


bool ScreenManager::transition_to_last_screen(){
    bool finished = true;
    
    for (auto& trans : transitions) {
        if (trans.scr1 == last_screen){
            finished = trans.fun(trans.scr1, trans.scr2);
        }
    }

    if (finished){
        auto tmp = last_screen;
        last_screen = current_screen;
        current_screen = tmp;
    }
    
    return finished;
}