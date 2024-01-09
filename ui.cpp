#include "ui.h"

#include <cstddef>
#include <cstdio>

#include "SDL_pixels.h"
#include "ball.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "player.h"
#include "state.h"
#include "util.h"

// Booleans for C
#define TRUE  1
#define FALSE 0

void initializeUI(SDL_Window* const window, SDL_Renderer* const renderer) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |=
		ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);
}

void imguiProcessEvent(const SDL_Event* const event) {
	ImGui_ImplSDL2_ProcessEvent(event);
}

void mainMenu(struct GameState* const state) {
	ImGui::Begin("Pong SDL");
	if (ImGui::Button("Start Game")) {
		state->gameInProgress = TRUE;
	}
	if (ImGui::Button("Settings")) {
		state->pauseMenu = Settings;
	}
	if (ImGui::Button("Quit Game")) {
		state->quitPressed = TRUE;
	}
	ImGui::End();
}

void pauseMenu(struct GameState* const state) {
	ImGui::Begin("Paused");
	if (ImGui::Button("Resume Game")) {
		state->pauseMenu = Unpaused;
	}
	if (ImGui::Button("Settings")) {
		state->pauseMenu = Settings;
	}
	ImGui::End();
}

void colorPicker(const char* const label, float* const input,
                 SDL_Color* const output) {
	ImGui::ColorPicker3(label, input);
	arrayToColor(input, output);
}

void persistenceMenu(struct GameState* const state) {
	if (ImGui::CollapsingHeader("Save to/Read from disk")) {
#define FILENAME_BUFLEN 50
		enum DiskOp : char {
			NONE = 0,
			WRITE,
			READ
		};

		static char filename[FILENAME_BUFLEN];
		enum DiskOp op = NONE;

		ImGui::InputText("Filename", filename, FILENAME_BUFLEN);
		if (ImGui::Button("Save")) {
			op = WRITE;
		}
		ImGui::SameLine();
		if (ImGui::Button("Load")) {
			op = READ;
		}
		if (op != NONE) {
			FILE* file = fopen(filename, op == READ ? "rb" : "wb");
			if (file != nullptr) {
				if (op == READ) {
					gameState_read(state, file);
					if (state->gameInProgress == 0) {
						ball_reset(state->ball);
					}
					player_update(state->player1, 0, 0, NULL);
					player_update(state->player2, 0, 0, NULL);
				} else {
					gameState_write(state, file);
				}
				fclose(file);
			}
		}
	}
}

void chooseLevel(const char* label, enum PaddleSkill& level) {
	if (ImGui::BeginCombo(label, skillToString(level))) {
		for (int lvl = 0; lvl < SKILL_END; lvl++) {
			if (ImGui::Selectable(skillToString((enum PaddleSkill)lvl),
			                      level == lvl)) {
				level = (enum PaddleSkill)lvl;
			}
			if (level == lvl) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
}

void settingsPanel(struct GameState* const state) {
	ImGui::Begin("Settings");

	if (ImGui::CollapsingHeader("Computer Controller Players")) {
		chooseLevel("Player 1##CC", state->player1->level);
		chooseLevel("Player 2##CC", state->player2->level);
	}

	if (ImGui::CollapsingHeader("Colors")) {
		colorPicker("Ball##Color", state->bColor, &state->ball->color);
		colorPicker("Player 1##Color", state->p1Color, &state->player1->color);
		colorPicker("Player 2##Color", state->p2Color, &state->player2->color);
	}

	if (ImGui::CollapsingHeader("Paddle Sizes")) {
		ImGui::InputInt("Player 1##Size", &state->player1->height);
		ImGui::InputInt("Player 2##Size", &state->player2->height);
	}

	if (ImGui::CollapsingHeader("Speeds")) {
		ImGui::InputFloat("Ball##Speed", &state->ball->speed);
		ImGui::InputInt("Player 1##Speed", &state->player1->speed);
		ImGui::InputInt("Player 2##Speed", &state->player2->speed);
	}

	persistenceMenu(state);

	if (ImGui::Button("Close")) {
		state->pauseMenu = (bool)state->gameInProgress ? Paused : Unpaused;
	}

	ImGui::End();
}

void renderUI(struct GameState* const state) {
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if (!(bool)state->gameInProgress) {
		mainMenu(state);
	}

	switch (state->pauseMenu) {
		case Paused:
			pauseMenu(state);
			break;
		case Settings:
			settingsPanel(state);
			break;
		default:
			break;
	}

	ImGui::Render();
}

void drawUI() {
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}
