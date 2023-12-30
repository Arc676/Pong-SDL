#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

#include "player.h"

extern const int BALL_SIZE;
extern const float DEFAULT_BALL_SPEED;

struct Ball {
	int x;
	int y;
	int vx;
	int vy;

	float speed;

	int fieldWidth;
	int fieldHeight;

	SDL_Color color;
	SDL_Rect rect;
};

enum BallResult {
	P1Scores,
	P2Scores,
	NoPoints
};

#ifdef __cplusplus
extern "C" {
#endif

void ball_init(struct Ball*, int, int);

void ball_write(const struct Ball*, FILE*);

void ball_read(struct Ball*, FILE*);

void ball_reset(struct Ball*);

enum BallResult ball_update(struct Ball*, const struct Player*,
                            const struct Player*);

void ball_render(const struct Ball*, SDL_Renderer*);

#ifdef __cplusplus
}
#endif

#endif
