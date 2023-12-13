#include "player.h"

#include <SDL2/SDL_render.h>

#include "util.h"

void player_init(int first, struct Player* const player, int width,
                 int height) {
	player->score = 0;
	player->speed = 1;
	player->y     = height / 2 + 5;
	initColor(&player->color, 255, 255, 255, 255);
	initRect(&player->rect, first ? 10 : width - 10, player->y, 10, 40);
}

void player_render(const struct Player* const player,
                   SDL_Renderer* const renderer) {
	setRenderColor(renderer, &player->color);
	SDL_RenderFillRect(renderer, &player->rect);
}