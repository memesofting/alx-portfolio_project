#include "main.h"

/**
 * free_maze - frees maze allocated memory
 * @maze: pointer to mazze array
 */
void free_maze(int **maze)
{
	int i;

	for (i = 0; i < MAP_SIZE; i++)
	{
		free(maze[i]);
	}
	free(maze);
}


/**
 * main - main function for running game
 * Return: 0 on success
 */

int main(void)
{
	srand(time(NULL));
	SDL_Instance instance;
	int **map;
	int game_loop;
	float playerX, playerY, planeX, planeY, playerDirX, playerDirY;

	playerX = 3.0f;
	playerY = 4.0f;
	playerDirX = -1.0f;
	playerDirY = 0.0f;
	planeX = 0.0f;  /*For FOV projection*/
	planeY = 0.66f; /*FOV set to 66°*/

	game_loop = 1;
	if (init_instance(&instance) != 0)
	{
		return (1);
	}
	map = random_maze();
	if (map == NULL)
	{
		SDL_DestroyRenderer(instance.renderer);
		SDL_DestroyWindow(instance.window);
		SDL_Quit();
		return (1);
	}
	while (game_loop)
	{
		game_loop = check_key();
		SDL_SetRenderDrawColor(instance.renderer, 0, 45, 0, 255);
		SDL_RenderClear(instance.renderer);
		/* draw walls here*/
		raycast(instance.renderer, playerX, playerY, playerDirX,
				playerDirY, planeX, planeY, map);
		SDL_RenderPresent(instance.renderer);
	}
	free_maze(map);
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
