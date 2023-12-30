#include "player.h"

#include <SDL2/SDL_render.h>
#include <stdio.h>

#include "SDL_pixels.h"
#include "util.h"

const int EDGE_MARGIN   = 10;
const int PLAYER_HEIGHT = 40;
const int PLAYER_WIDTH  = 10;

void player_init(int first, struct Player* const player, int width,
                 int height) {
	player->score = 0;

	player->speed  = 3;
	player->height = PLAYER_HEIGHT;

	player->x = first ? EDGE_MARGIN : width - EDGE_MARGIN - PLAYER_WIDTH;
	player->y = height / 2 - PLAYER_HEIGHT / 2;

	// NOLINTNEXTLINE(readability-magic-numbers)
	initColor(&player->color, 255, 255, 255, 255);
	initRect(&player->rect, player->x, player->y, PLAYER_WIDTH, player->height);
}

void player_write(const struct Player* const player, FILE* const file) {
	fwrite(&player->speed, sizeof(int), 1, file);
	fwrite(&player->height, sizeof(int), 1, file);
	fwrite(&player->color, sizeof(SDL_Color), 1, file);
}

void player_read(struct Player* const player, FILE* const file) {
	fread(&player->speed, sizeof(int), 1, file);
	fread(&player->height, sizeof(int), 1, file);
	fread(&player->color, sizeof(SDL_Color), 1, file);
}

void player_update(struct Player* const player, int up, int down) {
	if (up) {
		player->y -= player->speed;
	}
	if (down) {
		player->y += player->speed;
	}
	initRect(&player->rect, player->x, player->y, PLAYER_WIDTH, player->height);
}

void player_render(const struct Player* const player,
                   SDL_Renderer* const renderer) {
	setRenderColor(renderer, &player->color);
	SDL_RenderFillRect(renderer, &player->rect);
}
