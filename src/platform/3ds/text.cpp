#include "dimensions.hpp"
#include "text.hpp"
#include "draw.hpp"

#include <3ds.h>
#include <citro2d.h>

#include <array>
#include <unordered_map>
#include <iostream>
#include <sstream>

C2D_TextBuf g_staticBuf;
std::array<C2D_Text, 21> g_staticText;
std::unordered_map<char, C2D_Text> characters;
C2D_Font font = nullptr;
float font_px_size_ratio = 1.0f;

#define FIRST_ASCII_CHARACTER 32
#define LAST_ASCII_CHARACTER  126

void create_glyphs_with_selected_font(){
    int i;
    for (i = FIRST_ASCII_CHARACTER; i < LAST_ASCII_CHARACTER + 1; i++){
        char str[2] = {(char)i, '\0'};
		C2D_TextFontParse(&characters[i], font, g_staticBuf, str);
    }
    
    //	------------------------------Set strings---------------------------------
	// C2D_TextFontParse(&g_staticText[NO], 			        font, g_staticBuf, "No");
	// C2D_TextFontParse(&g_staticText[SI], 	                font, g_staticBuf, "Sí");

	// --------------Optimize strings----------------------
	for(C2D_Text& txt: g_staticText){
		C2D_TextOptimize(&txt);
	}

	for(auto& items: characters){
		C2D_TextOptimize(&items.second);
	}
	// ----------------------------------------------------

}

void graphics::text::init(){

	g_staticBuf = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
	set_font("CubicCoreMono");

}

bool graphics::text::set_font(const std::string& name){
    if (font)
        C2D_FontFree(font);
        
    std::stringstream s;
    
    s << "romfs:/gfx/fonts/" << name << ".bcfnt";

	font = C2D_FontLoad(s.str().c_str());
    create_glyphs_with_selected_font();

    float testheight = 1.0;

    C2D_TextGetDimensions(&characters['A'], 1.0, 1.0, NULL, &testheight);

    font_px_size_ratio = 1.0 / testheight;

    return font != NULL;
}

float graphics::text::px_to_size(int px) {
    return (px * 2.1) * font_px_size_ratio;
}

float graphics::text::pt_to_size(int pt) {
    return (pt * PPI) / 72.0 * font_px_size_ratio;
}

int graphics::text::pt_to_px(int pt) {
    return ((pt * 0.55) * PPI) / 72.0;
}

float graphics::text::get_text_width(const std::string &text, float size) {
    float width = 0.0f;
    for (auto ch : text) {
        width += characters[ch].width * size;
    }
    return width;
}

void graphics::text::draw_text(int x, int y, const std::string &text, float size, bool centered, const graphics::Color &color){
    const float VITA_TEXT_SIZE_ADJUSTMENT = 30; // make size in vita and 3DS the same
    //float scale_y = size / (30 * 72 / PPI);
    float scale_y = size;

    
    float text_width_offset = 0; // offset to center x in text  
    if (centered){
        for (auto ch : text) {
            text_width_offset += characters[ch].width * (scale_y) / 2;
        }
    }

    float xPos = x - text_width_offset;


    for(int i = 0; i < (int) text.length(); i++){
        const auto& letterFont = &characters[text.at(i)];
        C2D_DrawText(
            letterFont, 
            C2D_AtBaseline | C2D_WithColor,
            xPos, 
            y, 
            0.0f,
            scale_y,
            scale_y,
            color.to_RGBA32());

        xPos += letterFont->width * size;
    }

}



C2D_Text textFrom(const std::string& buff){
    
    uint word_count = 0;
    for(auto& ch : buff){
        if(ch == ' ')
            word_count++;
    }
    
    C2D_Text txt = {
        g_staticBuf,
        0,
        buff.length(),
        1,
        1,
        word_count,
        font
    };

    C2D_TextFontParse(&txt, font, g_staticBuf, buff.c_str());

    return txt;
}



void graphics::text::close()
{
	// Delete the text buffers
	C2D_TextBufDelete(g_staticBuf);
	C2D_FontFree(font);
}
