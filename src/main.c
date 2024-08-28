#include "main.h"

/**
 * main - main function for running game
 * Return: 0 on success
 */

int main(void)
{
	int game_loop;
	SDL_Event event;
	SDL_Instance instance;

	game_loop = 1;
	if (init_instance(&instance) != 0)
	{
		return (1);
	}

	while (game_loop)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					game_loop = 0;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						game_loop = 0;
					}
					break;
				default:
					break;
			}
		}
		SDL_SetRenderDrawColor(instance.renderer, 0, 45, 0, 255);
		SDL_RenderClear(instance.renderer);
		/* draw walls here*/
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
