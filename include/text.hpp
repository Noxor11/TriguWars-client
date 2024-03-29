#pragma once

#include "draw.hpp"

#include <charconv>
#include <string>

struct Settings;

namespace graphics{

    namespace text {
        
        void init();
        bool set_font(const std::string& name);
        float pt_to_size(int pt);
        float px_to_size(int px);
        // NOTE: Text is drawn from y to y - size. y is the bottom portion of the text
        void draw_text(int x, int y, const std::string& string, float size = pt_to_size(30), bool centered = false, const Color &color = Color::WHITE());
        int pt_to_px(int pt);
        float get_text_width(const std::string &text, float size);
        void close();

        #if __PSVITA__
        void reload_font();
        #endif
    }
}
