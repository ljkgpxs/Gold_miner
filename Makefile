CXX = g++

OBJECT = miner

SDL_CFLAGS = `pkg-config --cflags sdl2 SDL2_image`
SDL_LIBS = `pkg-config --libs sdl2 SDL2_image`

all:
	$(CXX) gamemain.c main.c -o $(OBJECT) $(SDL_CFLAGS) $(SDL_LIBS) 
clean:
	@rm -rf $(OBJECT)
	@echo "Clean Done"
