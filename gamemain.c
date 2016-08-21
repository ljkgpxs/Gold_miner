#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "common.h"

extern SDL_Texture *loadTexture(const char *filePath);

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
	SDL_Texture *goalDia, *goalGrade;
	SDL_Texture *goalBg;
	SDL_Rect diaRect, textRect;
	
	goalDia = loadTexture(imgFile[IMG_GOALDIA]);
	goalBg = loadTexture(imgFile[IMG_GOALBG]);
	goalGrade = loadRenderText(SDL_itoa(goal, goalString, 10), fontColor);
	while(running) {
		while(SDL_PollEvent(&keyEvent)) {
			if(keyEvent.type == SDL_QUIT) {
				running = false;
			}
		}

		diaRect.x = 300;
		diaRect.y = 200;
		diaRect.w = 200;
		diaRect.h = 100;
		textRect.x = 500;
		textRect.y = 300;
		textRect.w = 100;
		textRect.h = 80;
		SDL_RenderClear(winRenderer);
		SDL_RenderCopy(winRenderer, goalBg, NULL, NULL);
		SDL_RenderCopy(winRenderer, goalDia, NULL, &diaRect);
		SDL_RenderCopy(winRenderer, goalGrade, NULL, &textRect);
		SDL_RenderPresent(winRenderer);
	}
	SDL_DestroyTexture(goalBg);
	SDL_DestroyTexture(goalDia);
	SDL_DestroyTexture(goalGrade);

}

int startGame()
{
	gameFont = TTF_OpenFont("res/default.ttf", 40);
	setGoal(650);
	return 1;
}

