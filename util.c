#include "util.h"

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void initRect(SDL_Rect* const rect, int x, int y, int w, int h) {
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
void initColor(SDL_Color* color, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;
}

void setRenderColor(SDL_Renderer* const renderer,
                    const SDL_Color* const color) {
	SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
}