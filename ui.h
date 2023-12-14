#ifndef UI_H
#define UI_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#ifdef __cplusplus
extern "C" {
#endif

void initializeUI(SDL_Window*, SDL_Renderer*);

void imguiProcessEvent(const SDL_Event*);

void renderUI();

void drawUI();

#ifdef __cplusplus
}
#endif

#endif