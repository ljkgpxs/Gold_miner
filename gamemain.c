#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "common.h"

#define MAXRES	30;

extern SDL_Texture *loadTexture(const char *filePath);

struct resPos {
	int id;
	SDL_Point position;
};

struct levelInfo {
	int level;
	int levelGoal;
	int userGrade;
	int total;
	struct resPos *reses;
};

typedef struct resPos	resPos;
typedef struct levelInfo	levelInfo;

TTF_Font *gameFont = NULL;
SDL_Color fontColor = { 0x21, 0xd0, 0x1d };

SDL_Texture *loadRenderText(char *text, SDL_Color color)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(gameFont, text, color);
	if(textSurface == NULL) {
		printf("Failed to render text surface! %s\n", TTF_GetError());
		return NULL;
	}

	return SDL_CreateTextureFromSurface(winRenderer, textSurface);
}

void setGoal(int goal)
{
	bool running = true;
	char goalString[10];
	SDL_Texture *goalDia, *goalGrade, *goalBg;
	SDL_Rect diaRect, textRect;
	Uint32 startTime, frames;
	
	goalDia = loadTexture(imgFile[ID_GOALDIA]);
	goalBg = loadTexture(imgFile[ID_GOALBG]);
	goalGrade = loadRenderText(SDL_itoa(goal, goalString, 10), fontColor);
	frames = 0;
	diaRect.x = SCREEN_W / 2 - 320;
	diaRect.y = SCREEN_H / 2 - 180;
	diaRect.w = 640;
	diaRect.h = 340;
	textRect.x = SCREEN_W / 2;
	textRect.y = SCREEN_H / 2 - 30;
	textRect.w = 100;
	textRect.h = 70;
	while(running) {
		startTime = SDL_GetTicks();
		while(SDL_PollEvent(&keyEvent)) {
			if(keyEvent.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_RenderClear(winRenderer);
		SDL_RenderCopy(winRenderer, goalBg, NULL, NULL);
		SDL_RenderCopy(winRenderer, goalDia, NULL, &diaRect);
		SDL_RenderCopy(winRenderer, goalGrade, NULL, &textRect);
		SDL_RenderPresent(winRenderer);

		if(++frames >= FPS * 2)
			running = false;

		SDL_Delay(1000 / FPS - (SDL_GetTicks() -  startTime));
	}
	SDL_DestroyTexture(goalBg);
	SDL_DestroyTexture(goalDia);
	SDL_DestroyTexture(goalGrade);
}

int gameMain(levelInfo *level)
{
	int grade = level->userGrade;
	return grade;
}

int startGame()
{
	gameFont = TTF_OpenFont("res/default.ttf", 40);
	setGoal(65000);
	return 1;
}

