#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <math.h>

#include "common.h"
#include "gamemain.h"

TTF_Font *gameFont = NULL;
SDL_Color fontColor = { 0x21, 0xd0, 0x1d };
int userGrade = 0;

SDL_Texture *loadRenderText(const char *text, SDL_Color color)
{
	SDL_Surface *textSurface = TTF_RenderText_Solid(gameFont, text, color);
	if(textSurface == NULL) {
		printf("Failed to render text surface! %s\n", TTF_GetError());
		return NULL;
	}

	return SDL_CreateTextureFromSurface(winRenderer, textSurface);
}

unsigned int getNumDigit(int num)
{
	if(num == 0) return 1;
	unsigned int count = 0;
	while(num) {
		num /= 10;
		count++;
	}
	return count;
}

bool rectImpact(SDL_Rect a, SDL_Rect b)
{
	
	if((abs((a.x + a.w / 2) - (b.x + b.w / 2)) <= a.w / 2 + b.w / 2) && abs((a.y + a.h / 2) - (b.y + b.h / 2)) <= a.h / 2 + b.h / 2)
		return true;
	else
		return false;
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
	textRect.w = 20 * (getNumDigit(goal) + 1);
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
#ifndef _WIN32
		SDL_Delay(1000 / FPS - (SDL_GetTicks() -  startTime));
#endif
	}
	SDL_DestroyTexture(goalBg);
	SDL_DestroyTexture(goalDia);
	SDL_DestroyTexture(goalGrade);
}

levelInfo *getLevel(int lvl)
{
	if(lvl == 1) {
		levelInfo *currentLvl = (levelInfo *)malloc(sizeof(levelInfo));
		currentLvl->level = lvl;
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

void destroyLevel(levelInfo *lvl)
{
	free(lvl->reses);
	free(lvl);
	lvl = NULL;
}

int gameMain(levelInfo *level)
{
	SDL_Texture *gameBg, *resTexture[level->totalRes], *timeTexture, *levelTexture, *goalTexture, *gradeTexture, *hook;
	SDL_Rect resRect[level->totalRes], timeRect, levelRect, goalRect, gradeRect, hookRect;
	SDL_Point minerPin, hookPin;
	int startTime, levelTime, hookTimer, lineTimer;
	int lineLen = 0, catchedRes = 0;
	bool running = true, hookDown = false, hookGoRight = true, hookBack = false;
	levelTime = SDL_GetTicks();
	char levelStr[4] = { 0 };
	char goalStr[10] = { 0 };
	double hookAngle = 20;

	goalStr[0] = '$';

	gameBg = loadTexture(imgFile[ID_GAMEBG]);
	levelTexture = loadRenderText(SDL_itoa(level->level, levelStr, 10), fontColor);
	hook = loadTexture(imgFile[ID_HOOK]);

	SDL_itoa(level->levelGoal, &goalStr[1], 10);
	goalTexture = loadRenderText(goalStr, fontColor);
	for(int i = 0; i < level->totalRes; i++) {
		resTexture[i] = loadTexture(imgFile[level->reses[i].id]);
		resRect[i].x = level->reses[i].position.x;
		resRect[i].y = level->reses[i].position.y;
		SDL_QueryTexture(resTexture[i], NULL, NULL, &resRect[i].w, &resRect[i].h);
	}

	minerPin.x = 480;
	minerPin.y = 120;
	timeRect.x = 850; timeRect.y = 20;
	timeRect.w = 26; timeRect.h = 40;
	levelRect.x = 850; levelRect.y = 80;
	levelRect.w = 13 * getNumDigit(level->level);
	levelRect.h = 45;
	goalRect.x = 125; goalRect.y = 80;
	goalRect.w = 15 * (1 + getNumDigit(level->levelGoal));
	goalRect.h = 45;
	gradeRect.x = 130; gradeRect.y = 20;
	gradeRect.h = 45;
	hookTimer = 0;

	SDL_QueryTexture(hook, NULL, NULL, &hookRect.w, &hookRect.h);
	hookRect.x = minerPin.x - hookRect.w;
	hookRect.y = minerPin.y - hookRect.h + 50;
	hookPin.x = hookRect.w / 2;
	hookPin.y = 0;

	while(running) {
		char timeStr[3] = { 0 };
		char gradeStr[10] = { 0 };
		startTime = SDL_GetTicks();
		if((startTime - levelTime) / 1000 > 60)
			running = false;
		while(SDL_PollEvent(&keyEvent)) {
			if(keyEvent.type == SDL_QUIT)
				running = false;
			if(keyEvent.type == SDL_KEYDOWN)
				if(keyEvent.key.keysym.sym == SDLK_DOWN && !hookDown)
					hookDown = true;
		}

		if(!hookDown) {
			if(SDL_GetTicks() - hookTimer > 17) {
				hookTimer = SDL_GetTicks();
				if(hookGoRight) {
					hookAngle += 1;
					if(hookAngle >= 150)
						hookGoRight = false;
				} else {
					hookAngle -= 1;
					if(hookAngle <= 30)
						hookGoRight = true;
				}
			}
		} else {
			if(SDL_GetTicks() - lineTimer > 20) {
				lineTimer - SDL_GetTicks();
				lineLen++;
			}
		}

//		printf("%.0f ", hookAngle);
//		fflush(stdout);
//
		gradeStr[0] = '$';
		SDL_itoa(userGrade, &gradeStr[1], 10);
		gradeTexture = loadRenderText(gradeStr, fontColor);
		gradeRect.w = 15 * (getNumDigit(userGrade) + 1);;

		if(timeTexture)
			SDL_DestroyTexture(timeTexture);
		timeTexture = loadRenderText(SDL_itoa(60 - ((startTime - levelTime) / 1000), timeStr, 10), fontColor);

		SDL_RenderCopy(winRenderer, gameBg, NULL, NULL);
		SDL_RenderCopy(winRenderer, levelTexture, NULL, &levelRect);
		SDL_RenderCopy(winRenderer, timeTexture, NULL, &timeRect);
		SDL_RenderCopy(winRenderer, goalTexture, NULL, &goalRect);
		SDL_RenderCopy(winRenderer, gradeTexture, NULL, &gradeRect);
		SDL_RenderCopyEx(winRenderer, hook, NULL, &hookRect, 90 - hookAngle, &hookPin, SDL_FLIP_NONE);

		for(int i = 0; i < level->totalRes; i++) {
			SDL_RenderCopy(winRenderer, resTexture[i], NULL, &resRect[i]);
		}
		SDL_RenderPresent(winRenderer);

		for(int i = 0; i < level->totalRes; i++) {
			if(rectImpact(hookRect, resRect[i])) {
				catchedRes = i;
				hookBack = true;
				printf("Catched!\n");
				break;
			}
		}
#ifndef _WIN32

		SDL_Delay(PRE_FRAME_TICKS - (SDL_GetTicks() - startTime));
#endif
	}

	for(int i = 0; i < level->totalRes; i++) {
		SDL_DestroyTexture(resTexture[i]);
	}
	SDL_DestroyTexture(gameBg);
	SDL_DestroyTexture(timeTexture);
	SDL_DestroyTexture(levelTexture);
	return userGrade;
}

void gameOver(bool win)
{
	// Incomplete function
	if(win)
		printf("You Win %d\n", userGrade);
	else
		printf("You Lose %d\n", userGrade);
}

int startGame()
{
	int lvlNum = 1;
	bool win = false;
	levelInfo *lvl = NULL;
	gameFont = TTF_OpenFont("res/default.ttf", 40);
	
	while(1) {
		lvl = getLevel(lvlNum++);
		if(!lvl) {
			win = true;
			gameOver(win);
			break;
		}
		setGoal(lvl->levelGoal);
		if(gameMain(lvl) <= lvl->levelGoal) {
			gameOver(win);
			break;
		}
		destroyLevel(lvl);
	}
	return 1;
}

