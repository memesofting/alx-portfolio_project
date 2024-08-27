#include "main.h"

int main(void)
{
	int game_loop;

	game_loop = 1;
	SDL_Instance instance;
	if (init_instance(&instance) != 0)
	{
		return (1);
	}
	
	while (game_loop != 5)
	{
		SDL_SetRenderDrawColor(instance, renderer, 0, 45, 0, 0);
		SDL_RenderClear(instance, renderer);
		SDL_RenderPresent(instance, renderer);
		game_loop++;
	}
	return (0);
}
