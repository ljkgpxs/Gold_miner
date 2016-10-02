#pragma once

#include <SDL.h>

#define SCREEN_W	960
#define SCREEN_H	544

#define	FPS		60
#define PRE_FRAME_TICKS	1000 / FPS
enum statusGame{
	PROG_QUIT,
	START_GAME
};

enum resImgId {
	ID_STARTBG = 0,
	ID_LIGHT,
	ID_STARTBUTTON,
	ID_SSTONE,
	ID_BSTONE,
	ID_DIAMOND,
	ID_GOLD,
	ID_BAG,
	ID_GOALDIA,
	ID_GOALBG,
	ID_GAMEBG,
	ID_HOOK,
	ID_LINE
};

enum resSoundId {
	ID_MOUSEIN = 0,
	ID_DIG,
	ID_EXPLOSIVE,
	ID_HIGHVAL,
	ID_LOWVAL,
	ID_NORVAL,
	ID_PULL,
	ID_SCORE1,
	ID_SCORE2
};

extern SDL_Window *win;
extern SDL_Renderer *winRenderer;
extern SDL_Event keyEvent;
extern const char imgFile[][30];
extern const char sodFile[][30];

