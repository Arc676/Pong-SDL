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
	fwrite(state->ball, sizeof(struct Ball), 1, file);
	fwrite(state->player1, sizeof(struct Player), 1, file);
	fwrite(state->player2, sizeof(struct Player), 1, file);
}

void gameState_read(struct GameState* const state, FILE* const file) {
	fread(state->ball, sizeof(struct Ball), 1, file);
	fread(state->player1, sizeof(struct Player), 1, file);
	fread(state->player2, sizeof(struct Player), 1, file);
	gameState_cacheColors(state);
}
