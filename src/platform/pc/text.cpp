#include "draw.hpp"
#include "text.hpp"
#include "dimensions.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>

TTF_Font* font = nullptr;
float font_px_size_ratio = 1.0;

void graphics::text::init() {
    if (TTF_Init() < 0) {
        std::cout << "[CRITICAL] TTF_Init error: " << TTF_GetError() << std::endl;
        exit(1);
    }
}

bool graphics::text::set_font(const std::string& name) {
    std::stringstream str;
    str << name << ".ttf";
    font = TTF_OpenFont(str.str().c_str(), 50.0);
    if (font == NULL) {
        std::cout << "[CRITICAL] TTF_OpenFont error: " << TTF_GetError() << std::endl;
        exit(1);
    }

    TTF_SetFontSize(font, 50.0);
    int testsize = TTF_FontHeight(font);

    font_px_size_ratio = testsize / 50.0;
    return true;
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
    //int* width = (int*)malloc(sizeof(int));
    int width;
    TTF_MeasureText(font, text.c_str(), 512, &width, NULL);
    return width;
}


void graphics::text::draw_text(int x, int y, const std::string &string, float size, bool centered, const Color &color) {
    if (font == NULL) return;
    //WARN: EXPERIMENTAL: Reload font when a size is bigger to avoid upscaling due to cache
    //if (last_used_fontsize < size) {
    //    vita2d_free_font(font);
    //    font = vita2d_load_font_file(fontpath.c_str());
    //    last_used_fontsize = size;
    //}

    TTF_SetFontSize(font, size);

    float text_width_offset = 0; // offset to center x in text
    float text_width = graphics::text::get_text_width(string, size);
    if (centered){
        text_width_offset += text_width / 2;
    }

    // NOTE: Esto SEGURO que se puede hacer de una forma más limpia y OPTIMIZADA
    auto surface = TTF_RenderText_Solid(font, string.c_str(), {(u_char)color.r, (u_char)color.g, (u_char)color.b, (u_char)color.a});
    auto texture = SDL_CreateTextureFromSurface(graphics::get_renderer(), surface);
    SDL_Rect rect = {(int)(x + text_width_offset), (int)(y + text_width_offset), (int)text_width, TTF_FontHeight(font)};
    SDL_RenderCopy(graphics::get_renderer(), texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void graphics::text::close(){
    TTF_CloseFont(font);
}
