#pragma once

#include "draw.hpp"

#include <charconv>
#include <string>

struct Settings;


namespace graphics{

    namespace text {            
        
        void init();
        void draw_text(int x, int y, const Color &color, const std::string& string);
        void close();
    }
}