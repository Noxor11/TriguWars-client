#include "draw.hpp"
#include "text.hpp"

#include <vita2d.h>
#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <sstream>

vita2d_font* font = nullptr;

void graphics::text::init(){
}

bool graphics::text::set_font(const std::string& name) {
    std::stringstream str;
    str << "app0:gfx/fonts/" << name << ".ttf";
    font = vita2d_load_font_file(str.str().c_str());
    return font != NULL;
}

void graphics::text::draw_text(int x, int y, const std::string &string, unsigned int size, bool centered, const Color &color) {
    
    float text_width_offset = 0; // offset to center x in text  
    if (centered){
        text_width_offset += vita2d_font_text_width(font, size, string.c_str()) / 2;
    }

    if (font == NULL) return;
    vita2d_font_draw_text(font, x - text_width_offset, y, color.to_RGBA32(), size, string.c_str());
}

void graphics::text::close(){
    vita2d_free_font(font);
}
