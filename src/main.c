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
 * init_game - initialises SDL_Instance
 * @instance: pointer to SDL_Instance
 * @map: pointer to random maze
 * Return: 0 on success
 */
int init_game(SDL_Instance *instance, int ***map)
{
	if (init_instance(instance) != 0)
		return (1);
	*map = random_maze();
	if (*map == NULL)
	{
		SDL_DestroyRenderer(instance->renderer);
		SDL_DestroyWindow(instance->window);
		SDL_Quit();
		return (1);
	}

	return (0);
}

/**
 * game_loop - game loop function
 * @instance: pointer to SDL_Instance instance
 * @map: maze map array
 * @font: pointer to font file
 * @game_duration: duration for each game session
 */
void game_loop(SDL_Instance *instance, int **map,
		TTF_Font *font, Uint32 game_duration)
{
	int running = 1;
	float playerX = 3.0f, playerY = 4.0f, planeX = 0.0f, planeY = 0.66f;
	float playerDirX = -1.0f, playerDirY = 0.0f;
	Uint32 start_time = SDL_GetTicks(), elapsed_time;

	while (running)
	{
		/* Calculate elapsed time */
		elapsed_time = SDL_GetTicks() - start_time;
		int remaining_time = game_duration - elapsed_time;

		/* Check if time has run out */
		if (remaining_time <= 0)
		{
			printf("Time's up! You lasted %d seconds.\n", game_duration / 1000);

			/* Clear the screen before rendering Game Over */
			SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
			SDL_RenderClear(instance->renderer);

			game_over(instance->renderer, font);
			SDL_RenderPresent(instance->renderer);
			/* Add a small delay so the player can see the game-over screen */
			SDL_Delay(3000);
			break;
		}

		/* Handle input */
		running = check_input(&playerX, &playerY,
				&playerDirX, &playerDirY, &planeX, &planeY);
		/* Clear the screen */
		SDL_SetRenderDrawColor(instance->renderer, 0, 45, 0, 255);
		SDL_RenderClear(instance->renderer);
		/* Draw the game scene */
		raycast(instance->renderer, playerX, playerY,
				playerDirX, playerDirY, planeX, planeY, map);
		/*Draw mini map*/
		draw_mini_map(instance->renderer, playerX, playerY,
				playerDirX, playerDirY, map);
		/* Render the timer */
		render_timer(instance->renderer, font, remaining_time);
		/* Present the updated screen */
		SDL_RenderPresent(instance->renderer);
	}
}

/**
 * clean_up - frees all allocated memory
 * @instance: pointer to SDL_Instance instance
 * @map: maze map array
 * @font: pointer to font file
 */
void clean_up(SDL_Instance *instance, int **map, TTF_Font *font)
{
	free_maze(map);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(instance->renderer);
	SDL_DestroyWindow(instance->window);
	TTF_Quit();
	SDL_Quit();
}

/**
 * main - game entry point
 * Return: 0 on success
 */
int main(void)
{
	srand(time(NULL));
	TTF_Font *font;
	SDL_Instance instance;
	int **map;

	/* 90 seconds */
	Uint32 game_duration = 90000;

	/* Initialize SDL and the game */
	if (init_game(&instance, &map) != 0)
		return (1);
	/* Initialize SDL_ttf */
	if (TTF_Init() == -1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		return (1);
	}
	/* Load font */
	font = TTF_OpenFont("./Roboto-Medium.ttf", 24);
	if (!font)
	{
		printf("Failed to load font: %s\n", TTF_GetError());
		return (1);
	}
	/* Run the game loop */
	game_loop(&instance, map, font, game_duration);
	/* Clean up */
	clean_up(&instance, map, font);

	return (0);
}
