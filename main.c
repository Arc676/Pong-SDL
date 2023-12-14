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
#include <string.h>
#include <time.h>

#include "ball.h"
#include "player.h"
#include "score.h"
#include "ui.h"

const int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 1000;
const int FRAME_DELAY = 1000 / 60;

struct InputState {
	int up1, down1, up2, down2;
	int nextRally;
	int exitGame;
};

void pollInput(struct InputState* const state) {
	SDL_Event event;
	state->nextRally = 0;

	while (SDL_PollEvent(&event)) {
		imguiProcessEvent(&event);
		switch (event.type) {
			case SDL_KEYUP: {
				SDL_Scancode key = event.key.keysym.scancode;
				if (key == SDL_SCANCODE_Q) {
					state->exitGame = 1;
				} else if (key == SDL_SCANCODE_W) {
					state->up1 = 0;
				} else if (key == SDL_SCANCODE_S) {
					state->down1 = 0;
				} else if (key == SDL_SCANCODE_UP) {
					state->up2 = 0;
				} else if (key == SDL_SCANCODE_DOWN) {
					state->down2 = 0;
				} else if (key == SDL_SCANCODE_SPACE) {
					state->nextRally = 1;
				}
				break;
			}
			case SDL_KEYDOWN: {
				SDL_Scancode key = event.key.keysym.scancode;
				if (key == SDL_SCANCODE_W) {
					state->up1 = 1;
				} else if (key == SDL_SCANCODE_S) {
					state->down1 = 1;
				} else if (key == SDL_SCANCODE_UP) {
					state->up2 = 1;
				} else if (key == SDL_SCANCODE_DOWN) {
					state->down2 = 1;
				}
			}
		}
	}
}

void gameLoop(SDL_Renderer* const renderer) {
	// game elements
	struct Player player1, player2;
	struct Ball ball;
	int justScored = 0;

	struct ScoreRenderer srend;
	scoreRenderer_init(&srend, renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

	player_init(1, &player1, WINDOW_WIDTH, WINDOW_HEIGHT);
	player_init(0, &player2, WINDOW_WIDTH, WINDOW_HEIGHT);
	ball_init(&ball, WINDOW_WIDTH, WINDOW_HEIGHT);

	// input state
	struct InputState state;
	// NOLINTNEXTLINE (memset_s not in gcc)
	memset(&state, 0, sizeof(struct InputState));

	// render loop
	while (!state.exitGame) {
		// event polling
		pollInput(&state);

		// entity updates
		if (justScored) {
			if (state.nextRally) {
				ball_init(&ball, WINDOW_WIDTH, WINDOW_HEIGHT);
				justScored = 0;
			}
		} else {
			player_update(&player1, state.up1, state.down1);
			player_update(&player2, state.up2, state.down2);
			enum BallResult res = ball_update(&ball, &player1, &player2);
			if (res != NoPoints) {
				if (res == P1Scores) {
					player1.score++;
				} else {
					player2.score++;
				}
				justScored = 1;
			}
		}

		// rendering
		renderUI();

		// NOLINTNEXTLINE(readability-magic-numbers)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		player_render(&player1, renderer);
		player_render(&player2, renderer);
		ball_render(&ball, renderer);

		scoreRenderer_render(&srend, renderer, 1, player1.score);
		scoreRenderer_render(&srend, renderer, 0, player2.score);

		drawUI();

		// update screen
		SDL_RenderPresent(renderer);

		// 60 fps
		SDL_Delay(FRAME_DELAY);
	}
}

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

	initializeUI(win, renderer);

	gameLoop(renderer);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}