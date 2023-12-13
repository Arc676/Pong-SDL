#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct Player {
	int y;
	int speed;
	int score;
	SDL_Rect rect;
};

void player_init(int, struct Player*, int, int);

void player_update(struct Player*, int, int);

void player_render(const struct Player*, SDL_Renderer*);

#endif