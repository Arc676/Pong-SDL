#include "ui.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

void ui_init(struct UIState* const state, struct Player* const p1,
             struct Player* const p2) {
	state->player1      = p1;
	state->player2      = p2;
	state->showMainMenu = state->paused = 0;
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

void renderUI(struct UIState* const state) {
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	if ((bool)state->showMainMenu) {
		ImGui::Begin("Pong SDL");
		ImGui::End();
	}

	if ((bool)state->paused) {
		ImGui::Begin("Paused");
		if (ImGui::Button("Resume Game")) {
			state->paused = 0;
		}
		ImGui::End();
	}

	ImGui::Render();
}

void drawUI() {
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}