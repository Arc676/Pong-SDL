#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct Player;

struct Ball {
	int x;
	int y;
	int speed;
	SDL_Color color;
	SDL_Rect rect;
};

void ball_init(struct Ball*, int, int);

void ball_update(struct Ball*, struct Player*, struct Player*);

void ball_render(const struct Ball*, SDL_Renderer*);

#endif