#pragma once

SDL_Window *win = NULL;
SDL_Renderer *winRenderer = NULL;
SDL_Event keyEvent;

const char imgFile[][30] = {
	"res/img/startBg.jpg",
	"res/img/light.png",
	"res/img/startButton.png",
	"res/img/smallStone.png",
	"res/img/bigStone.png",
	"res/img/diamond.png",
	"res/img/gold.png",
	"res/img/bag.png",
	"res/img/goalDia.png",
	"res/img/diaBg.png",
	"res/img/gameBg.png",
	"res/img/hook.png",
	"res/img/line.png"
};

const char sodFile[][30] = {
	"res/sounds/mouseIn.wav",
	"res/sounds/dig.mp3",
	"res/sounds/explosive.wav",
	"res/sounds/highValue.wav",
	"res/sounds/lowValue.wav",
	"res/sounds/norValue.wav",
	"res/sounds/pull.wav",
	"res/sounds/score1.wav",
	"res/sounds/score2.wav"
};

