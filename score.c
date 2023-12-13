#include "score.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "util.h"

const int SCORE_X = 50;
const int SCORE_Y = 50;

void scoreRenderer_init(struct ScoreRenderer* score,
                        SDL_Renderer* const renderer, int width, int height) {
	static const size_t PATH_LENGTH = 50;
	for (int i = 0; i < DIGIT_COUNT; i++) {
		char path[PATH_LENGTH];
		sprintf(path, "img/%d.png", i);
		SDL_Surface* surface = IMG_Load(path);
		score->digits[i]     = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
	}

	score->screenWidth  = width;
	score->screenHeight = height;
}

void scoreRenderer_render(const struct ScoreRenderer* const srend,
                          SDL_Renderer* const renderer, int first,
                          unsigned score) {
	SDL_Rect rect;
	int digitCount = score > 0 ? (int)log10(score) + 1 : 1;

	int x = first ? SCORE_X
	              : srend->screenWidth - SCORE_X - SPRITE_SIZE * digitCount;
	if (digitCount == 1) {
		initRect(&rect, x, SCORE_Y, SPRITE_SIZE, SPRITE_SIZE);
		SDL_RenderCopy(renderer, srend->digits[score], NULL, &rect);
	} else {
		for (int i = 0; i < digitCount; i++) {
			// NOLINTBEGIN(readability-magic-numbers)
			unsigned digit = score % 10;
			score /= 10;
			// NOLINTEND(readability-magic-numbers)

			initRect(&rect, x, SCORE_Y, SPRITE_SIZE, SPRITE_SIZE);
			SDL_RenderCopy(renderer, srend->digits[digit], NULL, &rect);

			if (first) {
				x += SPRITE_SIZE;
			} else {
				x -= SPRITE_SIZE;
			}
		}
	}
}