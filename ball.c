#include "ball.h"

#include <SDL2/SDL_render.h>

#include "util.h"

const int BALL_SIZE = 10;

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void ball_init(struct Ball* ball, int width, int height) {
	ball->x     = width / 2 + BALL_SIZE / 2;
	ball->y     = height / 2 + BALL_SIZE / 2;
	ball->speed = 1;

	// NOLINTNEXTLINE(readability-magic-numbers)
	initColor(&ball->color, 255, 255, 255, 255);
	initRect(&ball->rect, ball->x, ball->y, BALL_SIZE, BALL_SIZE);
}

void ball_render(const struct Ball* const ball, SDL_Renderer* const renderer) {
	setRenderColor(renderer, &ball->color);
	SDL_RenderFillRect(renderer, &ball->rect);
}