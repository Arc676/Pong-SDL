#include "ball.h"

#include <SDL2/SDL_render.h>

#include "util.h"

void ball_init(struct Ball* ball, int width, int height) {
	ball->x     = width / 2 + 5;
	ball->y     = height / 2 + 5;
	ball->speed = 1;
	initRect(&ball->rect, ball->x, ball->y, 10, 10);
}

void ball_render(const struct Ball* const ball, SDL_Renderer* const renderer) {
	SDL_RenderFillRect(renderer, &ball->rect);
}