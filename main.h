#pragma once

SDL_Window *win = NULL;
SDL_Renderer *winRenderer = NULL;
SDL_Event keyEvent;

enum sourceImg {
	IMG_STARTBG = 0,
	IMG_LIGHT,
	IMG_STARTBUTTON,
	IMG_SSTONE,
	IMG_BSTONE,
	IMG_DIAMOND,
	IMG_GOLD,
	IMG_BAG
};

const char imgFile[20][30] = {
	"startBg.jpg",
	"light.png",
	"startButton.png",
	"smallStone.png",
	"bigStone.png",
	"diamond.png",
	"gold.png",
	"bag.png"
};

