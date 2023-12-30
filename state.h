#ifndef STATE_H
#define STATE_H

#ifdef __cplusplus
extern "C" {
#endif

enum PauseState : int {
	Unpaused = 0,
	Paused,
	Settings,
};

struct GameState {
	// main menu state
	int gameInProgress;
	int quitPressed;

	// pause state
	enum PauseState pauseMenu;

	// colors
	float bColor[3];
	float p1Color[3];
	float p2Color[3];

	// game elements
	struct Ball* ball;
	struct Player* player1;
	struct Player* player2;
};

void gameState_init(struct GameState*, struct Ball*, struct Player*,
                    struct Player*);

#ifdef __cplusplus
}
#endif

#endif
