#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

struct Ball;

extern const int EDGE_MARGIN;
extern const int PLAYER_HEIGHT;
extern const int PLAYER_WIDTH;

enum PaddleSkill : char {
	PLAYER = 0,
	FOLLOW_BALL,
	PRECOMPUTE,
	SKILL_END
};

struct Player {
	int x;
	int y;

	enum PaddleSkill level;

	int speed;
	int height;

	unsigned score;

	SDL_Color color;
	SDL_Rect rect;
};

#ifdef __cplusplus
extern "C" {
#endif

const char* skillToString(enum PaddleSkill);

void player_init(int, struct Player*, int, int);

void player_write(const struct Player*, FILE*);

void player_read(struct Player*, FILE*);

void player_update(struct Player*, int, int, const struct Ball*);

void player_render(const struct Player*, SDL_Renderer*);

#ifdef __cplusplus
}
#endif

#endif
