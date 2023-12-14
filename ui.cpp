#include "ui.h"

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

void initializeUI(SDL_Window* const window, SDL_Renderer* const renderer) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// NOLINTNEXTLINE(readability-identifier-length)
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |=
		ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer);
}

void imguiProcessEvent(const SDL_Event* const event) {
	ImGui_ImplSDL2_ProcessEvent(event);
}

void renderUI() {
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Render();
}

void drawUI() {
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}