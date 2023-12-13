#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>

const int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 1000;

int main() {
	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	SDL_Window* win =
		SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                     WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	unsigned flags         = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, flags);

	// render loop
	int exitGame = 0;
	while (!exitGame) {
		SDL_Event event;

		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYUP:
					if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
						exitGame = 1;
					}
			}
		}
	}

	return 0;
}