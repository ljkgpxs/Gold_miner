#pragma once

#include <SDL.h>

#define SCREEN_W	960
#define SCREEN_H	544

#define	FPS		60

enum {
	PROG_QUIT,
	START_GAME
};

enum sourceImg {
	IMG_STARTBG = 0,
	IMG_LIGHT,
	IMG_STARTBUTTON,
	IMG_SSTONE,
	IMG_BSTONE,
	IMG_DIAMOND,
	IMG_GOLD,
	IMG_BAG,
	IMG_GOALDIA,
	IMG_GOALBG
};

extern SDL_Window *win;
extern SDL_Renderer *winRenderer;
extern SDL_Event keyEvent;
extern const char imgFile[][30];

