#include "draw.hpp"
#include "text.hpp"

#include <vita2d.h>
#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

vita2d_pvf* pvf;

void graphics::text::init(){
    pvf = vita2d_load_default_pvf();
}

void graphics::text::draw_text(int x, int y, const Color &color, const std::string &string) {
    vita2d_pvf_draw_text(pvf, x, y, color.to_RGBA32(), 1.0f, string.c_str());
}

void graphics::text::close(){
    vita2d_free_pvf(pvf);
}
