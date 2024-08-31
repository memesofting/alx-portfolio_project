#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT  720
#define MAP_SIZE 15

typedef struct SDL_Instance
{
    SDL_Window *window;
    SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *instance);
int raycast(SDL_Renderer *renderer, float playerX, float playerY, float playerDirX, float playerDirY, float planeX, float planeY);

#endif
