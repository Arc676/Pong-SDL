#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL_render.h>

#define DIGIT_COUNT 10
#define SPRITE_SIZE 50

extern const int SCORE_X;
extern const int SCORE_Y;

struct ScoreRenderer {
	SDL_Texture* digits[DIGIT_COUNT];

	int screenWidth;
	int screenHeight;
};

void scoreRenderer_init(struct ScoreRenderer*, SDL_Renderer*, int, int);

void scoreRenderer_render(const struct ScoreRenderer*, SDL_Renderer*, int,
                          unsigned);

#endif