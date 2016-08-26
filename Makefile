CXX = g++

OBJECT = miner

SDL_CFLAGS = `pkg-config --cflags sdl2 SDL2_image SDL2_ttf SDL2_mixer`
SDL_LIBS = `pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer`

all:
	$(CXX) gamemain.c main.c -o $(OBJECT) $(SDL_CFLAGS) $(SDL_LIBS) -Wall 
clean:
	@rm -rf $(OBJECT)
	@echo "Clean Done"
