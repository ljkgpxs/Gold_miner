#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

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
	int totalRes;
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

inline unsigned int getNumDigit(int num)
{
	unsigned int count;
	while(num) {
		num /= 10;
		count++;
	}
	return count;
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
	goalString[0] = '$';
	SDL_itoa(goal, &goalString[1], 10);
	goalGrade = loadRenderText(goalString, fontColor);
	frames = 0;
	diaRect.x = SCREEN_W / 2 - 320;
	diaRect.y = SCREEN_H / 2 - 180;
	diaRect.w = 640;
	diaRect.h = 340;
	textRect.x = SCREEN_W / 2;
	textRect.y = SCREEN_H / 2 - 30;
	textRect.w = 25 * getNumDigit(goal);
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

levelInfo *getLevel(int lvl)
{
	if(lvl == 1) {
		levelInfo *currentLvl = (levelInfo *)malloc(sizeof(levelInfo));
		currentLvl->level = 200;
		currentLvl->levelGoal = 650;
		currentLvl->totalRes = 2;
		resPos *res = (resPos *)malloc(sizeof(resPos) * 2);;
		res[0].id = ID_GOLD;
		res[0].position.x = 100; res[0].position.y = 300;
		res[1].id = ID_BSTONE;
		res[1].position.x = 300; res[1].position.y = 400;
		currentLvl->reses = res;
		return currentLvl;
	}
	return NULL;
}

int gameMain(levelInfo *level)
{
	SDL_Texture *gameBg, *resTexture[level->totalRes], *timeTexture, *levelTexture, *goalTexture;
	SDL_Rect resRect[level->totalRes], timeRect, levelRect, goalRect;
	int grade = level->userGrade, startTime, levelTime;
	bool running = true;
	levelTime = SDL_GetTicks();
	char levelStr[4] = { 0 };
	char goalStr[10] = { 0 };
	goalStr[0] = '$';

	gameBg = loadTexture(imgFile[ID_GAMEBG]);
	levelTexture = loadRenderText(SDL_itoa(level->level, levelStr, 10), fontColor);
	SDL_itoa(level->levelGoal, &goalStr[1], 10);
	goalTexture = loadRenderText( goalStr, fontColor);
	for(int i = 0; i < level->totalRes; i++) {
		resTexture[i] = loadTexture(imgFile[level->reses[i].id]);
		resRect[i].x = level->reses[i].position.x;
		resRect[i].y = level->reses[i].position.y;
		SDL_QueryTexture(resTexture[i], NULL, NULL, &resRect[i].w, &resRect[i].h);
	}

	timeRect.x = 850; timeRect.y = 20;
	timeRect.w = 26; timeRect.h = 40;
	levelRect.x = 850; levelRect.y = 80;
	levelRect.w = 13 * getNumDigit(level->level);
	levelRect.h = 45;
	goalRect.x = 125; goalRect.y = 80;
	goalRect.w = 10 * getNumDigit(level->levelGoal);
	goalRect.h = 45;

	while(running) {
		char timeStr[2] = { 0 };
		startTime = SDL_GetTicks();
		if((startTime - levelTime) / 1000 > 60)
			running = false;
		while(SDL_PollEvent(&keyEvent)) {
			if(keyEvent.type == SDL_QUIT)
				running = false;
		}

		if(timeTexture)
			SDL_DestroyTexture(timeTexture);
		timeTexture = loadRenderText(SDL_itoa(60 - ((startTime - levelTime) / 1000), timeStr, 10), fontColor);

		SDL_RenderCopy(winRenderer, gameBg, NULL, NULL);
		SDL_RenderCopy(winRenderer, levelTexture, NULL, &levelRect);
		SDL_RenderCopy(winRenderer, timeTexture, NULL, &timeRect);
		SDL_RenderCopy(winRenderer, goalTexture, NULL, &goalRect);
		for(int i = 0; i < level->totalRes; i++) {
			SDL_RenderCopy(winRenderer, resTexture[i], NULL, &resRect[i]);
		}
		SDL_RenderPresent(winRenderer);
		SDL_Delay(PRE_FRAME_TICKS - (SDL_GetTicks() - startTime));
	}

	for(int i = 0; i < level->totalRes; i++) {
		SDL_DestroyTexture(resTexture[i]);
	}
	SDL_DestroyTexture(gameBg);
	SDL_DestroyTexture(timeTexture);
	SDL_DestroyTexture(levelTexture);
	return grade;
}

int startGame()
{
	gameFont = TTF_OpenFont("res/default.ttf", 40);
	levelInfo *lvl = getLevel(1);
	setGoal(lvl->levelGoal);
	gameMain(lvl);
	return 1;
}

