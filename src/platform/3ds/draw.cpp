#include "draw.hpp"

#include <3ds.h>
#include <citro2d.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>

#include <unistd.h>
#include <iostream>

C2D_SpriteSheet spriteSheet;

using namespace graphics;


// Settings initSettings(){
// 	Settings set;
// 	set.selected = INVERT_X;
	
// 	set.options.emplace(std::make_pair(INVERT_X, NO));
// 	set.options.emplace(std::make_pair(INVERT_Y, NO));

// 	return set;
// }

inline unsigned int Color::to_RGBA32() const {
    return C2D_Color32(this->r, this->g, this->b, this->a);
}


// -----------------------------------------------------------------------------------------------------
C3D_RenderTarget* top;
C3D_RenderTarget* bottom;
C3D_RenderTarget* selected_screen;



void stopAndClean(int error){
		switch (error){
			case -4:
				C3D_Fini();
				C2D_Fini();
			case -3:
				// textScene::exitTextScene();
				gfxExit();
				cfguExit();
			case -2: 
				SDL_Quit();		
		}
		
		romfsExit();
		gfxExit();

	}

int start_scene() {

    romfsInit();
    // apply_dsp_firm(); for sound to work

    // if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0){
    //     return -1;
    // }

    // if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) == -1)
    //     return -2;
    
    cfguInit(); // Allow C2D_FontLoadSystem to work
    gfxInitDefault();
    u8 system_language;
    CFGU_GetSystemLanguage(&system_language);
    // textScene::initTextScene(5);
    
    if(!C3D_Init(C3D_DEFAULT_CMDBUF_SIZE) || !C2D_Init(C2D_DEFAULT_MAX_OBJECTS))
        return -3;

    C2D_Prepare();		

    // Load graphics
    // spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
    // if (!spriteSheet) 
    //     return -4;
    

    // songs[0] = Mix_LoadMUS("romfs:/sound/music/background_loop.mp3");
    // songs[1] = Mix_LoadMUS("romfs:/sound/music/background_2.mp3");
    // songs[2] = Mix_LoadMUS("romfs:/sound/music/background_3.mp3");
    // songs[3] = Mix_LoadMUS("romfs:/sound/music/background_4.mp3");
    // songs[4] = Mix_LoadMUS("romfs:/sound/music/background_5.mp3");
    // songs[5] = Mix_LoadMUS("romfs:/sound/music/background_6.mp3");
    // songs[6] = Mix_LoadMUS("romfs:/sound/music/background_7.mp3");

    
    // if(!songs[0]){
    //     puts("Music could not be loaded.");
    //     sleep(3);
    //     SDL_Quit();
    //     gfxExit();
    //     return -5;
    // }


    // laser 			= Mix_LoadWAV("romfs:/sound/laser_shot.wav");
    // heavy_bullet 	= Mix_LoadWAV("romfs:/sound/heavy_bullet.wav");
    // hit 			= Mix_LoadWAV("romfs:/sound/8-bit-hit-7_NWM.wav");
    // player_hit		= Mix_LoadWAV("romfs:/sound/player_hit.wav");
    // game_over 		= Mix_LoadWAV("romfs:/sound/game_over.wav");
    // low_health 		= Mix_LoadWAV("romfs:/sound/low_health.wav");

    // move_up_menu 	= Mix_LoadWAV("romfs:/sound/move_up.wav");
    // move_down_menu 	= Mix_LoadWAV("romfs:/sound/move_down.wav");
    // confirm_select 	= Mix_LoadWAV("romfs:/sound/confirm_selection.wav");
    // click		 	= Mix_LoadWAV("romfs:/sound/click.wav");

    return 0;
}

void graphics::init() {
    int code = 0;
    if((code = start_scene()) < 0) {
        gfxInitDefault();
        consoleInit(GFX_TOP, NULL);
        printf("Scene not initialised.\nError code: %d\n\n", code);
        const char* msg;
        switch (code) {
            case -1: msg = "SDL_Audio could not be initialised.";	break;
            case -2: msg = "Could not open audio mixer.";			break;
            case -3: msg = "C2D could not be initialised.";			break;
            case -4: msg = "Spritesheet could not be loaded";		break;
        }
        puts(msg);
        puts("\nPress START to exit.");

        while(aptMainLoop()){
            hidScanInput();

            u32 kbDown = hidKeysDown();

            if (kbDown & KEY_START)
                break;
        }

        stopAndClean(code);
        exit(-1);
    }

    // top              = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    consoleInit(GFX_TOP, NULL);
	bottom           = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    selected_screen  = bottom;

}


void graphics::close() {
    // tell threads to exit & wait for them to exit
    // runThreads = false;
    // for (int i = 0; i < NUMTHREADS; i ++)
    // {
    //     threadJoin(threads[i], 1e8);
    //     threadFree(threads[i]);
    // }

    // SDL_Quit();
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    // textScene::exitTextScene();
    romfsExit();
    
    // Delete graphics
    // C2D_SpriteSheetFree(spriteSheet);
}

void graphics::start_frame() {

    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C2D_TargetClear(selected_screen, C2D_Color32(0, 0, 0, 0xFF));
    C2D_SceneBegin(selected_screen);
	
}

void graphics::end_frame() {
    C3D_FrameRate(60);
    C3D_FrameEnd(0);
    gspWaitForVBlank();
}

void graphics::draw_rectangle(int x, int y, int w, int h, const Color& color) {
	C2D_DrawRectangle(x, y, 0, w, h, color.to_RGBA32(), color.to_RGBA32(), color.to_RGBA32(), color.to_RGBA32());
}

void graphics::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color){
    C2D_DrawTriangle(x1, y1, color.to_RGBA32(), x2, y2, color.to_RGBA32(), x3, y3, color.to_RGBA32(), 0);
}

