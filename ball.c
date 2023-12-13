#include "ball.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <stdlib.h>

#include "util.h"

const int BALL_SIZE      = 10;
const int MAX_BALL_SPEED = 10;
const int MIN_BALL_SPEED = 1;

void ball_init(struct Ball* ball, int width, int height) {
	ball->x  = width / 2 + BALL_SIZE / 2;
	ball->y  = height / 2 + BALL_SIZE / 2;
	ball->vx = 1;
	// NOLINTNEXTLINE(concurrency-mt-unsafe)
	ball->vy = rand() % (MAX_BALL_SPEED - MIN_BALL_SPEED) + MIN_BALL_SPEED;

	ball->fieldHeight = height;

	// NOLINTNEXTLINE(readability-magic-numbers)
	initColor(&ball->color, 255, 255, 255, 255);
	initRect(&ball->rect, ball->x, ball->y, BALL_SIZE, BALL_SIZE);
}

// NOLINTBEGIN(readability-identifier-length)
void ball_update(struct Ball* ball, const struct Player* const p1,
                 const struct Player* const p2) {
	// NOLINTEND(readability-identifier-length)
	ball->x += ball->vx;
	ball->y += ball->vy;

	if (ball->y < 0 || ball->y > ball->fieldHeight) {
		ball->vy *= -1;
		ball->y += 2 * ball->vy;
	}

	SDL_bool hitP1 = SDL_HasIntersection(&ball->rect, &p1->rect);
	SDL_bool hitP2 = SDL_HasIntersection(&ball->rect, &p2->rect);
	if (hitP1 || hitP2) {
		ball->vx *= -1;
		ball->x += 2 * ball->vx;
	}
	initRect(&ball->rect, ball->x, ball->y, BALL_SIZE, BALL_SIZE);
}

void ball_render(const struct Ball* const ball, SDL_Renderer* const renderer) {
	setRenderColor(renderer, &ball->color);
	SDL_RenderFillRect(renderer, &ball->rect);
}