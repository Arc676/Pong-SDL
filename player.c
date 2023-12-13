#include "player.h"

#include <SDL2/SDL_render.h>

#include "util.h"

const int EDGE_MARGIN   = 10;
const int PLAYER_HEIGHT = 40;
const int PLAYER_WIDTH  = 10;

void player_init(int first, struct Player* const player, int width,
                 int height) {
	player->score = 0;
	player->speed = 3;
	player->x     = first ? EDGE_MARGIN : width - EDGE_MARGIN - PLAYER_WIDTH;
	player->y     = height / 2 - PLAYER_HEIGHT / 2;

	// NOLINTNEXTLINE(readability-magic-numbers)
	initColor(&player->color, 255, 255, 255, 255);
	initRect(&player->rect, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT);
}

// NOLINTNEXTLINE(readability-identifier-length)
void player_update(struct Player* const player, int up, int down) {
	if (up) {
		player->y -= player->speed;
	}
	if (down) {
		player->y += player->speed;
	}
	initRect(&player->rect, player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT);
}

void player_render(const struct Player* const player,
                   SDL_Renderer* const renderer) {
	setRenderColor(renderer, &player->color);
	SDL_RenderFillRect(renderer, &player->rect);
}