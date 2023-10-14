#include "input.hpp"
#include <psp2/ctrl.h>
#include <psp2/touch.h>

SceCtrlData pad;
SceCtrlData pad_prev;
SceTouchData* touchData;


namespace input {
    TouchPosition touch;
    Joystick joystick1;
    Joystick joystick2;
}

SceCtrlButtons translate_enum(input::Buttons button) {
    switch (button) {
        case input::BUTTON_CONFIRM: return SCE_CTRL_CROSS;
        case input::BUTTON_CANCEL: return SCE_CTRL_CIRCLE;
        
        case input::BUTTON_AUX_UP: return SCE_CTRL_TRIANGLE;
        case input::BUTTON_AUX_LEFT: return SCE_CTRL_SQUARE;
        case input::BUTTON_DPAD_LEFT: return SCE_CTRL_LEFT;
        case input::BUTTON_DPAD_RIGHT: return SCE_CTRL_RIGHT;
        case input::BUTTON_DPAD_UP: return SCE_CTRL_UP;
        case input::BUTTON_DPAD_DOWN: return SCE_CTRL_DOWN;
        case input::BUTTON_SELECT: return SCE_CTRL_SELECT;
        case input::BUTTON_START: return SCE_CTRL_START;

        default: return (SceCtrlButtons)NULL;
    }
};

void input::init() {
    sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG_WIDE);
    sceCtrlSetSamplingModeExt(SCE_CTRL_MODE_ANALOG_WIDE);
}

void input::scan() {
    pad_prev = pad;
    sceCtrlPeekBufferPositiveExt2(0, &pad, 1);
}

bool input::is_key_pressed(input::Buttons button) {
    SceCtrlButtons tbutton = translate_enum(button);
    return !(pad_prev.buttons & tbutton) && (pad.buttons & tbutton);
}

bool input::is_key_down(input::Buttons button) {
    SceCtrlButtons tbutton = translate_enum(button);
    return (pad.buttons & tbutton);
}

bool input::is_key_up(input::Buttons button) {
    SceCtrlButtons tbutton = translate_enum(button);
    return (pad_prev.buttons & tbutton) && !(pad.buttons & tbutton);
}

bool input::get_touch() {
    // NOTE: Esto solo lee el panel de táctil de arriba
    // https://github.com/mgba-emu/mgba/blob/ce374b15a3b0632472763a256f79be3f84c83831/src/platform/psp2/main.c#L68
    SceTouchData touchData;
    sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touchData, 1);

    if (touchData.reportNum < 1) return false;

    input::touch.x = touchData.report[0].x / 2.0f;
    input::touch.y = touchData.report[0].y / 2.0f;
    return true;
}
