#include "state.h"

#include <string.h>

#include "ball.h"
#include "player.h"
#include "util.h"

void gameState_init(struct GameState* const state, struct Ball* const ball,
                    struct Player* const p1, struct Player* const p2) {
	memset(state, 0, sizeof(struct GameState));

	for (int i = 0; i < 3; i++) {
		state->bColor[i] = state->p1Color[i] = state->p2Color[i] = 1;
	}

	colorToArray(state->bColor, &ball->color);
	colorToArray(state->p1Color, &p1->color);
	colorToArray(state->p2Color, &p2->color);

	state->ball    = ball;
	state->player1 = p1;
	state->player2 = p2;
}
