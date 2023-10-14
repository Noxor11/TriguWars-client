#pragma once

namespace input {

    struct touch_position{
	    unsigned short px;
	    unsigned short py;
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
        BUTTON_DPAD_DOWN
    };

    void init();
    void scan();

    bool is_key_pressed(Buttons button);
    bool is_key_down(Buttons button);
    bool is_key_up(Buttons button);

    /**
     * @returns true if being touched or false if not or if error
    */
    bool get_touch(touch_position* touch_position);

}
