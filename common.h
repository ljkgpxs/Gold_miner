#pragma once

#include <SDL.h>

#define SCREEN_W	960
#define SCREEN_H	544

#define	FPS		60

enum {
	PROG_QUIT,
	START_GAME
};

extern SDL_Window *win;
extern SDL_Renderer *winRenderer;
extern SDL_Event keyEvent;

