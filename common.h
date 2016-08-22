#pragma once

#include <SDL.h>

#define SCREEN_W	960
#define SCREEN_H	544

#define	FPS		60

enum {
	PROG_QUIT,
	START_GAME
};

enum resId {
	ID_STARTBG = 0,
	ID_LIGHT,
	ID_STARTBUTTON,
	ID_SSTONE,
	ID_BSTONE,
	ID_DIAMOND,
	ID_GOLD,
	ID_BAG,
	ID_GOALDIA,
	ID_GOALBG
};

extern SDL_Window *win;
extern SDL_Renderer *winRenderer;
extern SDL_Event keyEvent;
extern const char imgFile[][30];

