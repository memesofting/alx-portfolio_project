#include "main.h"

/**
 * init_instance - initialises SDL2 and creates window and renderer
 * @instance: pointer to SDL instance struct
 * Return: 0 on success
 */

int init_instance(SDL_Instance *instance)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Unable to initialise SDL: %s\n", SDL_GetError());
		return (1);
	}

	instance->window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL winto creation error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	instance->renderer = SDL_CreateRenderer(instance->window, -1, 0);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL renderer creation error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}
	return (0);
}
