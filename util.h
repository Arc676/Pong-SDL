#ifndef UTIL_H
#define UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

void initRect(SDL_Rect*, int, int, int, int);

void initColor(SDL_Color*, Uint8, Uint8, Uint8, Uint8);

void colorToArray(float*, const SDL_Color*);

void arrayToColor(const float*, SDL_Color*);

void setRenderColor(SDL_Renderer*, const SDL_Color*);

#ifdef __cplusplus
}
#endif

#endif
