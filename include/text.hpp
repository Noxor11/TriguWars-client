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
        void draw_text(int x, int y, const std::string& string, float size = px_to_size(30), bool centered = false, const Color &color = Color::WHITE());
        void close();
    }
}
