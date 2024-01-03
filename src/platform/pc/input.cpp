#include "input.hpp"

#include <SDL2/SDL.h>

namespace input {
    TouchPosition touch;
    Joystick joystick1;
    Joystick joystick2;
}

int KEYS[322];

void input::init() {
    for(int i = 0; i < 322; i++) { // init them all to false
        KEYS[i] = false;
    }
}

int translate_enum(input::Buttons button) {
    switch (button) {
        case input::BUTTON_START: return SDLK_RETURN;
        case input::BUTTON_SELECT: return SDLK_TAB;

        case input::BUTTON_CONFIRM: return SDLK_z;
        case input::BUTTON_CANCEL: return SDLK_x;
        case input::BUTTON_AUX_UP: return SDLK_s;
        case input::BUTTON_AUX_LEFT: return SDLK_a;

        case input::BUTTON_DPAD_UP: return SDLK_UP;
        case input::BUTTON_DPAD_DOWN: return SDLK_DOWN;
        case input::BUTTON_DPAD_RIGHT: return SDLK_RIGHT;
        case input::BUTTON_DPAD_LEFT: return SDLK_LEFT;

        default: return NULL;
    }
};

// KEYS
// 0 = unpressed
// 1 = just pressed
// 2 = held
// 3 = just released

void input::scan() {
    SDL_Event event;
    for(int i = 0; i < 322; i++) { // init them all to false
        if (KEYS[i] == 1) {
            KEYS[i] = 2;
        };
    }
    while (SDL_PollEvent(&event)) {
        // check for messages
        switch (event.type) {
            // exit if the window is closed
        case SDL_QUIT:
            break;
            // check for keypresses
        case SDL_KEYDOWN:
            KEYS[event.key.keysym.sym] = 1;
            break;
        case SDL_KEYUP:
            if (KEYS[event.key.keysym.sym] == 3) {
                KEYS[event.key.keysym.sym] = 0;
            } else {
                KEYS[event.key.keysym.sym] = 3;
            }
            break;
        default:
            break;
        }
    }
}

bool input::is_key_pressed(Buttons button) {
    return KEYS[translate_enum(button)] == 1;
}

bool input::is_key_held(Buttons button) {
    return KEYS[translate_enum(button)] == 1 || KEYS[translate_enum(button)] == 2;
}

bool input::is_key_up(Buttons button) {
    return KEYS[translate_enum(button)] == 3;
}
