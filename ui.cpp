#include "ui.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

// Booleans for C
#define TRUE  1
#define FALSE 0

void ui_init(struct UIState* const state, struct Player* const p1,
             struct Player* const p2) {
	memset(state, 0, sizeof(struct UIState));

	state->player1 = p1;
	state->player2 = p2;
}

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

void mainMenu(struct UIState* const state) {
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

void pauseMenu(struct UIState* const state) {
	ImGui::Begin("Paused");
	if (ImGui::Button("Resume Game")) {
		state->pauseMenu = Unpaused;
	}
	if (ImGui::Button("Settings")) {
		state->pauseMenu = Settings;
	}
	ImGui::End();
}

void settingsPanel(struct UIState* const state) {
	ImGui::Begin("Settings");

	if (ImGui::CollapsingHeader("Paddle Speeds")) {
		ImGui::InputInt("Player 1", &state->player1->speed);
		ImGui::InputInt("Player 2", &state->player2->speed);
	}

	if (ImGui::Button("Close")) {
		state->pauseMenu = (bool)state->gameInProgress ? Paused : Unpaused;
	}

	ImGui::End();
}

void renderUI(struct UIState* const state) {
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