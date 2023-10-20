#pragma once

#ifdef __3DS__
    #define BOTTOM_SCREEN_WIDTH		320
    #define BOTTOM_SCREEN_HEIGHT	240

    #define TOP_SCREEN_WIDTH        400
    #define TOP_SCREEN_HEIGHT       BOTTOM_SCREEN_HEIGHT

    #define TOP_WIDTH_CENTER		TOP_SCREEN_WIDTH  / 2
    #define TOP_HEIGHT_CENTER		TOP_SCREEN_HEIGHT / 2

    #define BOTTOM_WIDTH_CENTER		BOTTOM_SCREEN_WIDTH  / 2
    #define BOTTOM_HEIGHT_CENTER	BOTTOM_SCREEN_HEIGHT / 2

#elif defined __PSVITA__
    #define SCREEN_WIDTH            966
    #define SCREEN_HEIGHT           544
#endif
