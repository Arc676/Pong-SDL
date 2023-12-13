#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "player.h"

extern const int BALL_SIZE;
extern const int MAX_BALL_SPEED;
extern const int MIN_BALL_SPEED;

struct Ball {
	int x;
	int y;
	int vx;
	int vy;

	int fieldHeight;

	SDL_Color color;
	SDL_Rect rect;
};

void ball_init(struct Ball*, int, int);

void ball_update(struct Ball*, const struct Player*, const struct Player*);

void ball_render(const struct Ball*, SDL_Renderer*);

#endif