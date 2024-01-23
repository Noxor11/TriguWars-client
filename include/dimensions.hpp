#pragma once

#if defined __3DS__
    #define BOTTOM_SCREEN_WIDTH		320
    #define BOTTOM_SCREEN_HEIGHT	240

    #define TOP_SCREEN_WIDTH        400
    #define TOP_SCREEN_HEIGHT       BOTTOM_SCREEN_HEIGHT

    #define TOP_WIDTH_CENTER		TOP_SCREEN_WIDTH  / 2
    #define TOP_HEIGHT_CENTER		TOP_SCREEN_HEIGHT / 2

    #define BOTTOM_WIDTH_CENTER		BOTTOM_SCREEN_WIDTH  / 2
    #define BOTTOM_HEIGHT_CENTER	BOTTOM_SCREEN_HEIGHT / 2

    #define SCREEN_HEIGHT           TOP_SCREEN_HEIGHT

    #define TITLESCREEN_VSCREEN_SCALE 1.0f
    #define TITLESCREEN_VSCREEN_OFFSET_X 0

    // https://www.neogaf.com/threads/ppi-of-handhelds.987761/
    #define DEFAULT_PPI 120
#endif

#if defined(__PSVITA__) || defined(__PC__)
    #define SCREEN_WIDTH            966
    #define SCREEN_HEIGHT           544

    #define WIDTH_CENTER		SCREEN_WIDTH  / 2.0f
    #define HEIGHT_CENTER		SCREEN_HEIGHT / 2.0f

    #define TITLESCREEN_VSCREEN_SCALE 2.26f
    #define TITLESCREEN_VSCREEN_OFFSET_X 960.0f / 2 - (320 * 2.26f) / 2

    #if defined __VITA__
        #define DEFAULT_PPI 220
    #else
        #define DEFAULT_PPI 220
    #endif

#endif

