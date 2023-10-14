#include "text.hpp"
#include "draw.hpp"
#include <3ds.h>
#include <citro2d.h>

#include <array>
#include <unordered_map>

#include <iostream>

C2D_TextBuf g_staticBuf;
std::array<C2D_Text, 21> g_staticText;
std::unordered_map<char, C2D_Text> letters;
C2D_Font font;



void graphics::text::init(){

	g_staticBuf = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
	// font = C2D_FontLoad("romfs:/gfx/FredokaOne-Regular.bcfnt");
    font = C2D_FontLoadSystem(CFG_REGION_EUR);

	using namespace graphics::text;
	//	------------------------------Set strings---------------------------------
	// C2D_TextFontParse(&g_staticText[NO], 			        font, g_staticBuf, "No");
	// C2D_TextFontParse(&g_staticText[SI], 	                font, g_staticBuf, "Sí");


    int i;
    for (i = 'A'; i < 'Z' + 1; i++){
        char str[2] = {(char)i, '\0'};
		C2D_TextFontParse(&letters[i], font, g_staticBuf, str);
    }

    for ( i = 'a'; i < 'z' + 1; i++){
        char str[2] = {(char)i, '\0'};
		C2D_TextFontParse(&letters[i], font, g_staticBuf, str);
    }
    

	// --------------Optimize strings----------------------
	for(C2D_Text& txt: g_staticText){
		C2D_TextOptimize(&txt);
	}

	for(auto items: letters){
		C2D_TextOptimize(&items.second);
	}
	// ----------------------------------------------------
}

void graphics::text::draw_text(int x, int y, const graphics::Color &color, const std::string &text){

    const int size = 1;

    //	For every char in the score, convert to int and display it
    for(int i = 0, xPos = x; i < (int) text.length(); i++, xPos += 20){
        C2D_DrawText(&letters[text.at(i)], C2D_AtBaseline | C2D_AlignCenter | C2D_WithColor, xPos, y, 0.5f, size, size, color.to_RGBA32());
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