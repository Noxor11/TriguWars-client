#include "input.hpp"

#include <3ds.h>

#undef scanKeys
#undef keysHeld   
#undef keysDown   
#undef keysUp     
#undef touchRead  
#undef circleRead 


namespace input {
    TouchPosition touch;
    Joystick joystick1;
    Joystick joystick2;
}

constexpr u32 translate_enum(input::Buttons button) {
    switch (button) {
        case input::BUTTON_START:           return KEY_START;
        case input::BUTTON_SELECT:          return KEY_SELECT;

        case input::BUTTON_CONFIRM:         return KEY_A;
        case input::BUTTON_CANCEL:          return KEY_B;
        case input::BUTTON_AUX_UP:          return KEY_X;
        case input::BUTTON_AUX_LEFT:        return KEY_Y;
        
        case input::BUTTON_DPAD_LEFT:       return KEY_DLEFT;
        case input::BUTTON_DPAD_RIGHT:      return KEY_DRIGHT;
        case input::BUTTON_DPAD_UP:         return KEY_DUP;
        case input::BUTTON_DPAD_DOWN:       return KEY_DDOWN;

        case input::RIGHT_JOYSTICK_UP:      return KEY_CSTICK_UP;
        case input::RIGHT_JOYSTICK_DOWN:    return KEY_CSTICK_DOWN;
        case input::RIGHT_JOYSTICK_RIGHT:   return KEY_CSTICK_RIGHT;
        case input::RIGHT_JOYSTICK_LEFT:    return KEY_CSTICK_LEFT;

        default: return (u32)NULL;
    }
};

void input::init() {}

void input::scan(){
    hidScanInput();
    hidCircleRead((circlePosition*)&input::joystick1);
    hidCstickRead((circlePosition*)&input::joystick2);
}

bool input::is_key_pressed(Buttons button) {
    return hidKeysHeld() & translate_enum(button);
}

bool input::is_key_down(Buttons button) {
    return hidKeysDown() & translate_enum(button);
}

bool input::is_key_up(Buttons button) {
    return hidKeysUp() & translate_enum(button);
}

bool input::get_touch() {
    hidTouchRead((touchPosition*) &touch);
    return !(input::touch.x <= 0 || input::touch.y <= 0); 
}
