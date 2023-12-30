#include "state.h"

#include <stdio.h>
#include <string.h>

#include "ball.h"
#include "player.h"
#include "util.h"

void gameState_cacheColors(struct GameState* const state) {
	colorToArray(state->bColor, &state->ball->color);
	colorToArray(state->p1Color, &state->player1->color);
	colorToArray(state->p2Color, &state->player2->color);
}

void gameState_init(struct GameState* const state, struct Ball* const ball,
                    struct Player* const p1, struct Player* const p2) {
	memset(state, 0, sizeof(struct GameState));

	state->ball    = ball;
	state->player1 = p1;
	state->player2 = p2;

	gameState_cacheColors(state);
}

void gameState_write(const struct GameState* const state, FILE* const file) {
	ball_write(state->ball, file);
	player_write(state->player1, file);
	player_write(state->player2, file);
}

void gameState_read(struct GameState* const state, FILE* const file) {
	ball_read(state->ball, file);
	player_read(state->player1, file);
	player_read(state->player2, file);
	gameState_cacheColors(state);
}
