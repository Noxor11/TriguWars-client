#pragma once

namespace input {

    struct TouchPosition {
	    unsigned short x;
	    unsigned short y;
    };

    struct Joystick {
        signed short x;
        signed short y;
    };

    enum Buttons {
        BUTTON_START,
        BUTTON_SELECT,

        BUTTON_CONFIRM,
        BUTTON_CANCEL,
        BUTTON_AUX_UP,
        BUTTON_AUX_LEFT,
        
        BUTTON_DPAD_LEFT,
        BUTTON_DPAD_RIGHT,
        BUTTON_DPAD_UP,
        BUTTON_DPAD_DOWN,

        RIGHT_JOYSTICK_UP,
        RIGHT_JOYSTICK_DOWN,
        RIGHT_JOYSTICK_RIGHT,
        RIGHT_JOYSTICK_LEFT,

        BUTTON_COUNT
    };

    extern TouchPosition touch;
    extern Joystick joystick1;
    extern Joystick joystick2;


    void init();
    void scan();

    bool is_key_pressed(Buttons button);
    bool is_key_held(Buttons button);
    bool is_key_up(Buttons button);

    /**
     * @returns true if being touched or false if not or if error
    */
    bool get_touch();
}
