// #include "text.hpp"


// C2D_TextBuf g_staticBuf;
// std::array<C2D_Text, 21> g_staticText;
// std::array<C2D_Text, 10> scoreNumberText;
// C2D_Font font;



// void graphics::text::init(){

// 	g_staticBuf = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
// 	font = C2D_FontLoad("romfs:/gfx/FredokaOne-Regular.bcfnt");

// 	using namespace graphics::text;
// 	//	------------------------------Set strings---------------------------------
// 	C2D_TextFontParse(&g_staticText[NO], 			        font, g_staticBuf, "No");
// 	C2D_TextFontParse(&g_staticText[SI], 	                font, g_staticBuf, "Sí");
// 	C2D_TextFontParse(&g_staticText[CREAR_TORNEO],          font, g_staticBuf, "Crear Torneo");
// 	C2D_TextFontParse(&g_staticText[UNIRSE_TORNEO], 		font, g_staticBuf, "Unirse a un torneo");
// 	C2D_TextFontParse(&g_staticText[TITULO], 		        font, g_staticBuf, "Piedra, Papel, o Tijera!");
// 	C2D_TextFontParse(&g_staticText[VOLVER], 		        font, g_staticBuf, "Volver");
// 	C2D_TextFontParse(&g_staticText[TORNEO_PUBLICO], 		font, g_staticBuf, "Torneo Público");
// 	C2D_TextFontParse(&g_staticText[TORNEO_PRIVADO], 	    font, g_staticBuf, "Torneo Privado");
// 	C2D_TextFontParse(&g_staticText[INTR_NOMBRE_TORNEO], 	font, g_staticBuf, "Introducir nombre del torneo");
// 	C2D_TextFontParse(&g_staticText[ENVIAR], 		        font, g_staticBuf, "Enviar");
// 	C2D_TextFontParse(&g_staticText[CONEXION_EXITOSA], 		font, g_staticBuf, "Conexión Exitosa");
// 	C2D_TextFontParse(&g_staticText[INTR_NOMBRE_USUARIO], 	font, g_staticBuf, "Introducir nombre de usuario");
// 	C2D_TextFontParse(&g_staticText[CLAVE_TORNEO],          font, g_staticBuf, "Clave del torneo:");
// 	C2D_TextFontParse(&g_staticText[GANASTE],               font, g_staticBuf, "Has ganado la partida!");
// 	C2D_TextFontParse(&g_staticText[PERDISTE],              font, g_staticBuf, "Has perdido la partida.");
// 	C2D_TextFontParse(&g_staticText[JUGADORES_EN_LOBBY],    font, g_staticBuf, "Jugadores en lobby:");



// 	//	Numbers
// 	for (int i = 0; i < (int) scoreNumberText.size(); i++){
// 		C2D_TextFontParse(&scoreNumberText[i], font, g_staticBuf, std::to_string(i).c_str());
// 	}
// 	//	---------------------------------------------------------------------------


// 	// --------------Optimize strings----------------------
// 	for(C2D_Text& txt: g_staticText){
// 		C2D_TextOptimize(&txt);
// 	}


// 	for(C2D_Text& txt: scoreNumberText){
// 		C2D_TextOptimize(&txt);
// 	}
// 	// ----------------------------------------------------
// }


// void drawBottomMenuText(){
// 	const float size = 1;
// 	// Draw white title below
// 	C2D_DrawText(&g_staticText[TITULO], 0, 20, 40, 0.5f, size, size);


// }
// void drawTopMenuText(){
// 	// const int size = 1;
// 	// C2D_DrawText(&g_staticText[PLAY], C2D_WithColor, 100, BOTTOM_HEIGHT_CENTER - 30, 0.5f, size, size, C2D_Color32f(255.0f,255.0f,255.0f,255.0f));
// 	// C2D_DrawText(&g_staticText[SETTINGS_TXT], C2D_WithColor, 100, BOTTOM_HEIGHT_CENTER, 0.5f, size, size, C2D_Color32f(255.0f,255.0f,255.0f,255.0f));
// 	// C2D_DrawText(&g_staticText[NEXT_SONG_TXT], C2D_WithColor, 100, BOTTOM_HEIGHT_CENTER + 30, 0.5f, size, size, C2D_Color32f(255.0f,255.0f,255.0f,255.0f));

// }


// void drawWonBottom(){
// 	const int size = 2;
// 	C2D_DrawText(&g_staticText[GANASTE], C2D_WithColor, 100, 0, 0.5f, size, size, C2D_Color32f(255.0f,255.0f,255.0f,255.0f));
// }



// void drawC2DText(const C2D_Text* text, Params* params, u32 color){
// 	const float size = 0.5f;

// 	if(text && params)
// 		C2D_DrawText(text, C2D_WithColor | C2D_AtBaseline | C2D_AlignCenter, params->x, params->y, 0, size, size, color);
// }

// C2D_Text* getTextAt(int pos){
// 	return &g_staticText[pos];
// }

// C2D_Text textFrom(const char* buff, size_t size){
	
// 	uint word_count = 0;
// 	for(auto& ch : std::string(buff, size)){
// 		if(ch == ' ')
// 			word_count++;
// 	}


	
// 	C2D_Text txt = {
// 		g_staticBuf,
// 		0,
// 		size,
// 		1,
// 		1,
// 		word_count,
// 		font
// 	};

// 	C2D_TextFontParse(&txt, font, g_staticBuf, buff);

// 	return txt;
// }



// void exitTextScene(void)
// {
// 	// Delete the text buffers
// 	C2D_TextBufDelete(g_staticBuf);
// 	C2D_FontFree(font);

// }