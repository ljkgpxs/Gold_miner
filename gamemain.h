#pragma once

#include <SDL.h>

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

extern int startGame();
