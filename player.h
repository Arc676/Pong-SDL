#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

extern const int EDGE_MARGIN;
extern const int PLAYER_HEIGHT;
extern const int PLAYER_WIDTH;

struct Player {
	int x;
	int y;
	int speed;
	int score;
	SDL_Color color;
	SDL_Rect rect;
};

void player_init(int, struct Player*, int, int);

void player_update(struct Player*, int, int);

void player_render(const struct Player*, SDL_Renderer*);

#endif