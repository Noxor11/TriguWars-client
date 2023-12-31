#include "draw.hpp"
#include "text.hpp"

#include <3ds.h>
#include <citro2d.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>
#include <SDL/SDL_mixer.h>

#include <unistd.h>
#include <iostream>
#include <array>

C2D_SpriteSheet spriteSheet;

using namespace graphics;

inline unsigned int Color::to_RGBA32() const {
    return C2D_Color32(this->r, this->g, this->b, this->a);
}


// -----------------------------------------------------------------------------------------------------
C3D_RenderTarget* top1;
C3D_RenderTarget* top2;

C3D_RenderTarget* bottom;
C3D_RenderTarget* selected_screen_target;

namespace graphics {
    Screen selected_screen;
}



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

    if(!C3D_Init(C3D_DEFAULT_CMDBUF_SIZE) || !C2D_Init(C2D_DEFAULT_MAX_OBJECTS))
        return -3;

    C2D_Prepare();		

    // Load graphics
    // spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
    // if (!spriteSheet) 
    //     return -4;
    

    // songs[0] = Mix_LoadMUS("romfs:/sound/music/background_loop.mp3");
    
    // if(!songs[0]){
    //     puts("Music could not be loaded.");
    //     sleep(3);
    //     SDL_Quit();
    //     gfxExit();
    //     return -5;
    // }


    // laser 			= Mix_LoadWAV("romfs:/sound/laser_shot.wav");

    top1             = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    top2             = C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);
#ifdef DEBUG
    consoleInit(GFX_BOTTOM, NULL);
#else
	bottom           = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
#endif
    selected_screen_target  = top1;

    text::init();

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

    #ifndef DEBUG
    C2D_TargetClear(bottom, C2D_Color32(0, 0, 0, 0xFF));
    #endif
    C2D_TargetClear(top1, C2D_Color32(0, 0, 0, 0xFF));
    C2D_TargetClear(top2, C2D_Color32(0, 0, 0, 0xFF));
    C2D_SceneBegin(selected_screen_target);
}

void graphics::set_screen(Screen scr) {
    switch (scr) {
        case TOP1: selected_screen_target = top1; graphics::selected_screen = TOP1; break;
        case TOP2: selected_screen_target = top2; graphics::selected_screen = TOP2; break;
        case BOTTOM: selected_screen_target = bottom; graphics::selected_screen = BOTTOM; break;
    
        default: break;
    }
    // https://github.com/devkitPro/3ds-examples/blob/master/graphics/gpu/both_screens/source/main.c
    //C3D_FrameDrawOn(selected_screen_target);
    C2D_SceneBegin(selected_screen_target);
    // C2D_TargetClear(selected_screen_target, C2D_Color32(0, 0, 0, 0xFF));
}

void graphics::end_frame() {
    C3D_FrameRate(60);
    C3D_FrameEnd(0);
    // gspWaitForVBlank();
}

void graphics::draw_rectangle(int x, int y, int w, int h, const Color& color) {
	C2D_DrawRectangle(x, y, 0, w, h, color.to_RGBA32(), color.to_RGBA32(), color.to_RGBA32(), color.to_RGBA32());
}


void graphics::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& color){
    C2D_DrawTriangle(x1, y1, color.to_RGBA32(), x2, y2, color.to_RGBA32(), x3, y3, color.to_RGBA32(), 0);
}

void graphics::draw_line(int x1, int y1, int x2, int y2, const Color &color) {
    C2D_DrawLine(x1, y1, color.to_RGBA32(), x2, y2, color.to_RGBA32(), 1, 1);
}

void graphics::draw_vertices(const Vector2 *vertices, int n_vertices, const Color& color, bool fill) {
    if (fill) {
        // Triangle fan
        for (int i = 0; i < n_vertices - 2; i++) {
        C2D_DrawTriangle(
            vertices[0].x, vertices[0].y,
            color.to_RGBA32(),
            vertices[i+1].x, vertices[i+1].y,
            color.to_RGBA32(),
            vertices[i+2 % n_vertices].x,  vertices[i+2 % n_vertices].y,
            color.to_RGBA32(), 0);
        }
    } else {        
        int i;
        for (i = 0; i < n_vertices - 1; ++i) {
            graphics::draw_line(vertices[i].x, vertices[i].y, vertices[i+1].x, vertices[i+1].y, color);
        }
        graphics::draw_line(vertices[i].x, vertices[i].y, vertices[0].x, vertices[0].y, color);
    }
}
