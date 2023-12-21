#include "draw.hpp"
#include "text.hpp"
#include "dimensions.hpp"

#include <vita2d.h>
#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <sstream>

vita2d_font* font = nullptr;
float font_px_size_ratio = 1.0;
std::string fontpath = "";
int last_used_fontsize = 0;

void graphics::text::init(){
}

bool graphics::text::set_font(const std::string& name) {
    std::stringstream str;
    str << "app0:gfx/fonts/" << name << ".ttf";
    fontpath = str.str();
    font = vita2d_load_font_file(str.str().c_str());
    return font != NULL;

    int testsize = vita2d_font_text_height(font, 100, "This is test text that shouldn't have subscripts");

    font_px_size_ratio = testsize / 50.0;
}

float graphics::text::px_to_size(int px) {
    return (px * 2.10) * font_px_size_ratio;
}

float graphics::text::pt_to_size(int pt) {
    return (pt * PPI) / 72.0 * font_px_size_ratio;
}

int graphics::text::pt_to_px(int pt) {
    return ((pt*0.55) * PPI) / 72.0;
}

float graphics::text::get_text_width(const std::string &text, float size) {
    return vita2d_font_text_width(font, size, text.c_str());
}

void graphics::text::reload_font() {
    vita2d_free_font(font);
    font = vita2d_load_font_file(fontpath.c_str());
}

void graphics::text::draw_text(int x, int y, const std::string &string, float size, bool centered, const Color &color) {
    if (font == NULL) return;
    //WARN: EXPERIMENTAL: Reload font when a size is bigger to avoid upscaling due to cache
    //if (last_used_fontsize < size) {
    //    vita2d_free_font(font);
    //    font = vita2d_load_font_file(fontpath.c_str());
    //    last_used_fontsize = size;
    //}

    float text_width_offset = 0; // offset to center x in text  
    if (centered){
        text_width_offset += vita2d_font_text_width(font, size, string.c_str()) / 2;
    }

    vita2d_font_draw_text(font, x - text_width_offset, y, color.to_RGBA32(), size, string.c_str());
}

void graphics::text::close(){
    vita2d_free_font(font);
}
