#pragma once

class VirtualScreen {
    public:
        float offset_x;
        float offset_y;
        float width;
        float height;
        float scale;

        float translate_x(float x);
        float translate_y(float y);
        float translate_w(float w);
        float translate_h(float h);
        VirtualScreen(float x, float y, float w, float h, float scale);
};
