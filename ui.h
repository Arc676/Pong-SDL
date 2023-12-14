#ifndef UI_H
#define UI_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#include "ball.h"
#include "player.h"

#ifdef __cplusplus
extern "C" {
#endif

enum PauseState : int {
	Unpaused = 0,
	Paused,
	Settings,
};

struct UIState {
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

void ui_init(struct UIState*, struct Ball*, struct Player*, struct Player*);

void initializeUI(SDL_Window*, SDL_Renderer*);

void imguiProcessEvent(const SDL_Event*);

void renderUI(struct UIState*);

void drawUI();

#ifdef __cplusplus
}
#endif

#endif