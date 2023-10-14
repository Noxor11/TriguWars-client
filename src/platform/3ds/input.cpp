#include "input.hpp"

#include <3ds.h>

#undef scanKeys
#undef keysHeld   
#undef keysDown   
#undef keysUp     
#undef touchRead  
#undef circleRead 


void input::scan(){
    hidScanInput();
}

unsigned int input::keys_down() {
    return hidKeysDown();
}

unsigned int input::keys_downRepeat() {
    return hidKeysDownRepeat();
}

unsigned int input::keys_held() {
    return hidKeysHeld();
}

unsigned int input::keys_up() {
    return hidKeysUp();
}

void input::touch(touch_position* touch_position) {
    return hidTouchRead((touchPosition*) touch_position);
}
