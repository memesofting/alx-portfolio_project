#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define MAP_SIZE 25

typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *instance);
int raycast(SDL_Renderer *renderer, float playerX, float playerY, float playerDirX, float playerDirY, float planeX, float planeY, int **map);
int check_key(float *playerX, float *playerY, float *playerDirX, float *playerDirY, float *planeX, float *planeY);
void init_maze(int **maze);
int is_valid(int x, int y, int **maze);
void generate_maze(int x, int y, int **maze);
int **random_maze(void);


#endif
