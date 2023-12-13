#include "util.h"

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters, readability-identifier-length)
void initRect(SDL_Rect* const rect, int x, int y, int w, int h) {
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}