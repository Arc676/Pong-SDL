#include "util.h"

void colorToArray(float* arr, const SDL_Color* const color) {
	// NOLINTBEGIN(readability-magic-numbers)
	arr[0] = (float)color->r / 255;
	arr[1] = (float)color->g / 255;
	arr[2] = (float)color->b / 255;
	// NOLINTEND(readability-magic-numbers)
}

void arrayToColor(const float* const arr, SDL_Color* const color) {
	// NOLINTBEGIN(readability-magic-numbers)
	color->r = (Uint8)(arr[0] * 255);
	color->g = (Uint8)(arr[1] * 255);
	color->b = (Uint8)(arr[2] * 255);
	// NOLINTEND(readability-magic-numbers)
}

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