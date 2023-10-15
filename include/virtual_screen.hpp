#pragma once

class VirtualScreen {
    public:
        float offset_x;
        float offset_y;
        float width;
        float height;
        float scale;

        float translate_x(float x) const;
        float translate_y(float y) const;
        float translate_w(float w) const;
        float translate_h(float h) const;
        VirtualScreen(float x, float y, float w, float h, float scale);
};
