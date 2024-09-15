#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define MAP_SIZE 25
#define MAP_SCALE 10

/**
 * struct SDL_Instance - struct to store window and renderer pointers
 * @window: pointer to window address
 * @renderer: pointer to renderer address
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *instance);
int raycast(SDL_Renderer *renderer, float playerX, float playerY,
	float playerDirX, float playerDirY, float planeX,
	float planeY, int **map);
int check_input(float *playerX, float *playerY, float *playerDirX,
		float *playerDirY, float *planeX, float *planeY);
void init_maze(int **maze);
int is_valid(int x, int y, int **maze);
void generate_maze(int x, int y, int **maze);
int **random_maze(void);
void check_mouse(SDL_Event *event, float *playerDirX,
float *playerDirY, float *planeX, float *planeY);
int check_key(SDL_Event *event, float *playerX, float *playerY,
float *playerDirX, float *playerDirY, float *planeX, float *planeY);
void render_timer(SDL_Renderer *renderer, TTF_Font *font,
		int remaining_time);
void game_over(SDL_Renderer *renderer, TTF_Font *font);
void draw_mini_map(SDL_Renderer *renderer, float playerX, float playerY,
		float playerDirX, float playerDirY, int **map);

#endif
