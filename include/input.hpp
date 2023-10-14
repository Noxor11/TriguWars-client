#pragma once

namespace input {

    struct touch_position{
	    unsigned short px;
	    unsigned short py;
    };

    void scan();

    unsigned int keys_down();
    unsigned int keys_downRepeat();
    unsigned int keys_held();
    unsigned int keys_up();

    void touch(touch_position* touch_position);

}