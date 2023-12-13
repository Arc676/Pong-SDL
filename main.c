#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "player.h"

const int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 1000;
const int FRAME_DELAY = 1000 / 60;

int main() {
	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	srand(time(NULL));

	SDL_Window* win =
		SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                     WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	unsigned flags         = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, flags);

	// game elements
	struct Player player1, player2;
	struct Ball ball;
	int waitToStart = 0, justScored = 0;

	player_init(1, &player1, WINDOW_WIDTH, WINDOW_HEIGHT);
	player_init(0, &player2, WINDOW_WIDTH, WINDOW_HEIGHT);
	ball_init(&ball, WINDOW_WIDTH, WINDOW_HEIGHT);

	// render loop
	int exitGame = 0;
	while (!exitGame) {
		SDL_Event event;

		// controls
		static int up1 = 0, down1 = 0;
		static int up2 = 0, down2 = 0;

		// event polling
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYUP: {
					SDL_Scancode key = event.key.keysym.scancode;
					if (key == SDL_SCANCODE_Q) {
						exitGame = 1;
					} else if (key == SDL_SCANCODE_W) {
						up1 = 0;
					} else if (key == SDL_SCANCODE_S) {
						down1 = 0;
					} else if (key == SDL_SCANCODE_UP) {
						up2 = 0;
					} else if (key == SDL_SCANCODE_DOWN) {
						down2 = 0;
					} else if (key == SDL_SCANCODE_SPACE) {
						waitToStart = 0;
					}
					break;
				}
				case SDL_KEYDOWN: {
					SDL_Scancode key = event.key.keysym.scancode;
					if (key == SDL_SCANCODE_W) {
						up1 = 1;
					} else if (key == SDL_SCANCODE_S) {
						down1 = 1;
					} else if (key == SDL_SCANCODE_UP) {
						up2 = 1;
					} else if (key == SDL_SCANCODE_DOWN) {
						down2 = 1;
					}
				}
			}
		}

		// entity updates
		if (!waitToStart) {
			if (justScored) {
				ball_init(&ball, WINDOW_WIDTH, WINDOW_HEIGHT);
				justScored = 0;
			} else {
				player_update(&player1, up1, down1);
				player_update(&player2, up2, down2);
				enum BallResult res = ball_update(&ball, &player1, &player2);
				if (res != NoPoints) {
					if (res == P1Scores) {
						player1.score++;
					} else {
						player2.score++;
					}
					justScored  = 1;
					waitToStart = 1;
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