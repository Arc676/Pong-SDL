#include "ball.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "player.h"
#include "util.h"

const int BALL_SIZE            = 10;
const float DEFAULT_BALL_SPEED = 14.1421F;  // 10 * sqrt(2)

void ball_init(struct Ball* ball, int width, int height) {
	ball->fieldWidth  = width;
	ball->fieldHeight = height;
	ball->speed       = DEFAULT_BALL_SPEED;

	// NOLINTNEXTLINE(readability-magic-numbers)
	initColor(&ball->color, 255, 255, 255, 255);

	ball_reset(ball);
}

void ball_write(const struct Ball* const ball, FILE* const file) {
	fwrite(&ball->speed, sizeof(ball->speed), 1, file);
	fwrite(&ball->color, sizeof(SDL_Color), 1, file);
}

void ball_read(struct Ball* const ball, FILE* const file) {
	fread(&ball->speed, sizeof(ball->speed), 1, file);
	fread(&ball->color, sizeof(SDL_Color), 1, file);
}

void ball_reset(struct Ball* const ball) {
	ball->x = ball->fieldWidth / 2 + BALL_SIZE / 2;
	ball->y = ball->fieldHeight / 2 + BALL_SIZE / 2;
// NOLINTBEGIN(concurrency-mt-unsafe)
#define ANGLE_RANGE 60
#define MIN_ANGLE   20
#if ANGLE_RANGE + MIN_ANGLE >= 90
#error Invalid angle range
#endif
#define TO_RADIANS (M_PI / 180)
	double angle = (rand() % ANGLE_RANGE + MIN_ANGLE) * TO_RADIANS;
	if (rand() % 2 == 0) {
		angle *= -1;
	}
	ball->vx = (int)(ball->speed * cos(angle));
	ball->vy = (int)(ball->speed * sin(angle));
	if (rand() % 2 == 0) {
		ball->vx *= -1;
	}
	// NOLINTEND(concurrency-mt-unsafe)

	initRect(&ball->rect, ball->x, ball->y, BALL_SIZE, BALL_SIZE);
}

enum BallResult ball_update(struct Ball* ball, const struct Player* const p1,
                            const struct Player* const p2) {
	ball->x += ball->vx;
	ball->y += ball->vy;

	if (ball->y < 0 || ball->y > ball->fieldHeight - BALL_SIZE) {
		ball->vy *= -1;
		ball->y += 2 * ball->vy;
	}

	SDL_bool hitP1 = SDL_HasIntersection(&ball->rect, &p1->rect)
	                 && abs(ball->x - p1->x) < PLAYER_WIDTH / 2;
	SDL_bool hitP2 = SDL_HasIntersection(&ball->rect, &p2->rect)
	                 && abs(ball->x - p2->x) < PLAYER_WIDTH / 2;
	if (hitP1 || hitP2) {
		ball->vx *= -1;
		ball->x += 2 * ball->vx;
	}
	initRect(&ball->rect, ball->x, ball->y, BALL_SIZE, BALL_SIZE);

	if (ball->x < 0) {
		return P2Scores;
	}
	if (ball->x > ball->fieldWidth - BALL_SIZE) {
		return P1Scores;
	}
	return NoPoints;
}

void ball_render(const struct Ball* const ball, SDL_Renderer* const renderer) {
	setRenderColor(renderer, &ball->color);
	SDL_RenderFillRect(renderer, &ball->rect);
}
