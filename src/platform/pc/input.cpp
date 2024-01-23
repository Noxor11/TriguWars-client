#include "input.hpp"

#include <SDL2/SDL.h>

namespace input {
    TouchPosition touch;
    Joystick joystick1;
    Joystick joystick2;
}

int KEYS[322];

const Uint8* prevstate = SDL_GetKeyboardState(nullptr);
const Uint8* state = SDL_GetKeyboardState(nullptr);

void input::init() {
    prevstate = state;
    state = SDL_GetKeyboardState(nullptr);
}

int translate_enum(input::Buttons button) {
    switch (button) {
        case input::BUTTON_START: return SDL_SCANCODE_RETURN;
        case input::BUTTON_SELECT: return SDL_SCANCODE_TAB;

        case input::BUTTON_CONFIRM: return SDL_SCANCODE_Z;
        case input::BUTTON_CANCEL: return SDL_SCANCODE_X;
        case input::BUTTON_AUX_UP: return SDL_SCANCODE_S;
        case input::BUTTON_AUX_LEFT: return SDL_SCANCODE_A;

        case input::BUTTON_DPAD_UP: return SDL_SCANCODE_UP;
        case input::BUTTON_DPAD_DOWN: return SDL_SCANCODE_DOWN;
        case input::BUTTON_DPAD_RIGHT: return SDL_SCANCODE_RIGHT;
        case input::BUTTON_DPAD_LEFT: return SDL_SCANCODE_LEFT;

        default: return (int)NULL;
    }
};


bool pad[input::BUTTON_COUNT];
bool prevpad[input::BUTTON_COUNT];

void input::scan() {
    SDL_PumpEvents();
    state = SDL_GetKeyboardState(nullptr);

    for (int i = 0; i < input::BUTTON_COUNT; i++) {
        prevpad[i] = pad[i];
        pad[i] = 0;
        if (state[translate_enum((input::Buttons)i)]) pad[i] = true;
    }

    joystick1.x = 0;
    joystick1.y = 0;
    if (state[SDL_SCANCODE_H]) {
        joystick1.x -= 127;
    }
    if (state[SDL_SCANCODE_L]) {
        joystick1.x += 127;
    }
    if (state[SDL_SCANCODE_J]) {
        joystick1.y -= 127;
    }
    if (state[SDL_SCANCODE_K]) {
        joystick1.y += 127;
    }
}

bool input::is_key_pressed(Buttons button) {
    return pad[button] && !prevstate[button];
}

bool input::is_key_held(Buttons button) {
    return state[button];
}

bool input::is_key_up(Buttons button) {
    return !state[button] && prevstate[button];
}
