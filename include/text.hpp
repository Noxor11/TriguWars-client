#pragma once

#include "draw.hpp"

#include <charconv>
#include <string>

struct Settings;


namespace graphics{

    namespace text {
        
        void init();
        bool set_font(const std::string& name);
        void draw_text(int x, int y, const std::string& string, unsigned int size = 30, const Color &color = Color::WHITE());
        void close();
    }
}
