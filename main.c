#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include "ball.h"
#include "player.h"

const int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 1000;
const int FRAME_DELAY = 1000 / 60;

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

	// game elements
	struct Player player1, player2;  // NOLINT(readability-isolate-declaration)
	struct Ball ball;

	player_init(1, &player1, WINDOW_WIDTH, WINDOW_HEIGHT);
	player_init(0, &player2, WINDOW_WIDTH, WINDOW_HEIGHT);
	ball_init(&ball, WINDOW_WIDTH, WINDOW_HEIGHT);

	// render loop
	int exitGame = 0;
	while (!exitGame) {
		SDL_Event event;

		// event polling
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYUP:
					if (event.key.keysym.scancode == SDL_SCANCODE_Q) {
						exitGame = 1;
					}
			}
		}

		// rendering
		// NOLINTNEXTLINE(readability-magic-numbers)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		player_render(&player1, renderer);
		player_render(&player2, renderer);
		ball_render(&ball, renderer);

		// update screen
		SDL_RenderPresent(renderer);

		// 60 fps
		SDL_Delay(FRAME_DELAY);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}