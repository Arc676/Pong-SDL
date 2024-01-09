#include "player.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>

#include "ball.h"
#include "util.h"

const int EDGE_MARGIN   = 10;
const int PLAYER_HEIGHT = 40;
const int PLAYER_WIDTH  = 10;

const char* skillToString(const enum PaddleSkill level) {
	switch (level) {
		case PLAYER:
			return "Human";
		case FOLLOW_BALL:
			return "Computer (easy)";
		case PRECOMPUTE:
			return "Computer (hard)";
		default:
			return "Unknown player control mode";
	}
}

void player_init(int first, struct Player* const player, int width,
                 int height) {
	player->score = 0;
	player->level = PLAYER;

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

int computeExactTarget(const struct Player* const player,
                       const struct Ball* const ball) {
	const int dx = player->x - ball->x;
	const int dt = dx / ball->vx;
	const int dy = ball->vy * dt;
	// determine final ball Y coordinate ignoring field boundaries
	const int yf = ball->y + dy;
	// number of times the ball would bounce off the boundaries
	const int traversals = yf / ball->fieldHeight - (yf < 0);
	// true final Y coordinate
	int target = yf - traversals * ball->fieldHeight;
	if (traversals % 2 != 0) {
		target = ball->fieldHeight - target;
	}
	return target;
}

void player_computerUpdate(struct Player* const player,
                           const struct Ball* const ball) {
	// do nothing if ball isn't moving
	if (ball->vx == 0 || ball->vy == 0) {
		return;
	}
	// do nothing if ball is moving away from paddle
	if ((ball->vx > 0) == (ball->x > player->x)) {
		return;
	}
	int target;
	switch (player->level) {
		case FOLLOW_BALL:
			target = ball->y;
			break;
		case PRECOMPUTE:
			target = computeExactTarget(player, ball);
			break;
		default:
			return;
	}
	// account for ball size
	target += BALL_SIZE / 2;
	// aim to hit with paddle center
	const int current = player->y + player->height / 2;
	if (abs(current - target) > player->speed) {
		if (current < target) {
			player->y += player->speed;
		} else if (current > target) {
			player->y -= player->speed;
		}
	}
}

void player_humanUpdate(struct Player* const player, int up, int down) {
	if (up) {
		player->y -= player->speed;
	}
	if (down) {
		player->y += player->speed;
	}
}

void player_update(struct Player* const player, int up, int down,
                   const struct Ball* const ball) {
	if (ball) {
		if (player->level == PLAYER) {
			player_humanUpdate(player, up, down);
		} else {
			player_computerUpdate(player, ball);
		}
	}
	initRect(&player->rect, player->x, player->y, PLAYER_WIDTH, player->height);
}

void player_render(const struct Player* const player,
                   SDL_Renderer* const renderer) {
	setRenderColor(renderer, &player->color);
	SDL_RenderFillRect(renderer, &player->rect);
}
