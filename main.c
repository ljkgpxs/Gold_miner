#include <stdio.h>
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_timer.h>

#include "common.h"
#include "gamemain.h"
#include "main.h"

int Init_SDL()
{
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		printf("SDL initialize failed! %s\n", SDL_GetError());
		return 0;
	} else {
		win = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
		winRenderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if(winRenderer == NULL) {
			printf("Failed to create window renderer! %s\n", SDL_GetError());
			return 0;
		}
	}

	if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
		printf("SDL image initialize failed! %s\n", IMG_GetError());
		return 0;
	}

	return 1;
}

void Close_SDL()
{
	// printf("Close SDL\n");
	SDL_DestroyRenderer(winRenderer);
	SDL_DestroyWindow(win);
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture *loadTexture(const char *filePath)
{
	SDL_Surface *loadedSurface;
	SDL_Texture *newTexture;

	loadedSurface = IMG_Load(filePath);
	if(loadedSurface == NULL) {
		printf("Failed to load file %s! %s\n", filePath, IMG_GetError());
		newTexture = NULL;
	} else {
		newTexture = SDL_CreateTextureFromSurface(winRenderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

int circleToRect(SDL_Rect *rect, int x, int y, float radius)
{
	//rect->x = x > radius ? x - radius : 0;
	//rect->y = y > radius ? y - radius : 0;
	rect->x = x - radius;
	rect->y = y - radius;
	
	rect->h = radius * 2;
	rect->w = radius *2;
}

bool mouseInside(SDL_Point mouse, SDL_Rect area)
{
	if(mouse.x >= area.x && mouse.x <= area.x + area.w && mouse.y >= area.y && mouse.y <= area.y + area.h)
		return true;
	else
		return false;
}

int readyAnimation()
{
	SDL_Texture *light, *startBg, *startButton;
	SDL_Rect lightRect, buttonRect, buttonClip[2];
	float lightRadius = 200;
	bool running = true, increase = false;
	int mouseOver = 0;
	Uint32 startTime;

	light = loadTexture(imgFile[IMG_LIGHT]);
	startBg = loadTexture(imgFile[IMG_STARTBG]);
	startButton = loadTexture(imgFile[IMG_STARTBUTTON]);
	buttonClip[0].x = buttonClip[0].y = 0;
	buttonClip[0].w = 160;
	buttonClip[0].h = 43;
	buttonClip[1].x = 0;
	buttonClip[1].y = 43;
	buttonClip[1].w = 160;
	buttonClip[1].h = 55;
	buttonRect.x = 180;
	buttonRect.y = 135;
	buttonRect.w = 160;

	while(running) {
		startTime = SDL_GetTicks();
		while(SDL_PollEvent(&keyEvent)) {
			if(keyEvent.type == SDL_QUIT)
				running = false;
			if(keyEvent.type == SDL_KEYDOWN)
				if(keyEvent.key.keysym.sym == SDLK_SPACE) {
					SDL_DestroyTexture(light);
					SDL_DestroyTexture(startBg);
					return START_GAME;
				}
			if(keyEvent.type == SDL_MOUSEMOTION || keyEvent.type == SDL_MOUSEBUTTONDOWN) {
				SDL_Point mouse;
				SDL_GetMouseState(&mouse.x, &mouse.y);
				if(mouseInside(mouse, buttonRect)) {
					if(keyEvent.type == SDL_MOUSEBUTTONDOWN)
						return START_GAME;
					buttonRect.h = 55;
					mouseOver = 1;
				} else {
					buttonRect.h = 43;
					mouseOver = 0;
				}
			}
		}

		circleToRect(&lightRect, 250, 150, lightRadius);
		SDL_RenderClear(winRenderer);
		SDL_RenderCopy(winRenderer, startBg, NULL, NULL);
		SDL_RenderCopy(winRenderer, light, NULL, &lightRect);
		SDL_RenderCopy(winRenderer, startButton, &buttonClip[mouseOver], &buttonRect);
		SDL_RenderPresent(winRenderer);
		if(increase) {
			lightRadius += 0.6;
			if(lightRadius > 250)
				increase = false;
		} else {
			lightRadius -= 0.7;
			if(lightRadius < 170)
				increase = true;
		}
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - startTime));
	}

	SDL_DestroyTexture(light);
	SDL_DestroyTexture(startBg);
	SDL_DestroyTexture(startButton);
	return PROG_QUIT;
}

int main(int argc, char **argv)
{
	if(!Init_SDL()) {
		return 1;
	}
	
	atexit(Close_SDL);

	if(readyAnimation() == PROG_QUIT) {
		return 0;
	} else {
		startGame();
	}

	return 0;
}

