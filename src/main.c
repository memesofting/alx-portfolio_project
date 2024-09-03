#include "main.h"

/*int maze[MAP_SIZE][MAP_SIZE];*/
/*int** maze;*/
/*passage movement direction*/
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

void init_maze(int** maze)
{
	/*0 = wall, 1 = passage*/
	int i, j;

	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			/*set all cells as wall*/
			maze[i][j] = 0;
		}
	}
}

int is_valid(int x, int y, int** maze)
{
	return x >= 0 && x < MAP_SIZE &&
	y >= 0 && y < MAP_SIZE && maze[y][x] == 0;
}

void generate_maze(int x, int y, int** maze)
{
	/*nx and ny are neighbor grids*/
	int i, r, temp, nx, ny;
	int direction[4] = {0, 1, 2, 3};

	maze[y][x] = 1;
	for (i = 0; i < 4; i++)
	{
		r = rand() % 4;
		temp = direction[i];
		direction[i] = direction[r];
		direction[r] = temp;
	}

	/*check neighbors in random order*/
	for (i = 0; i < 4; i++)
	{
		nx = x + dx[direction[i]] * 2;
		ny = y + dy[direction[i]] * 2;
		/*check if grid is a wall*/
		if (is_valid(nx, ny, maze))
		{
			/*create passage*/
			maze[y + dy[direction[i]]][x + dx[direction[i]]] = 1;
			/*recuresively generate maze*/
			generate_maze(nx, ny, maze);
		}
	}
}

int** random_maze(void)
{
	// int maze[MAP_SIZE][MAP_SIZE];
	int** maze;
	int i, j;

	maze = malloc(MAP_SIZE * sizeof(int*));
	if (maze == NULL)
	{
		return (NULL);
	}
    for (i = 0; i < MAP_SIZE; i++) {
        maze[i] = malloc(MAP_SIZE * sizeof(int));
		if (maze[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				free(maze[j]);
			}
			free(maze);
			return (NULL);
		}
    }

    // Initialize and generate the maze
    init_maze(maze);
    generate_maze(1, 1, maze);

    return maze;
}

void free_maze(int** maze)
{  
	int i;
    for (i = 0; i < MAP_SIZE; i++) {  
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
	SDL_Event event;
	SDL_Instance instance;
	int** map;
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
		raycast(instance.renderer, playerX, playerY, playerDirX, playerDirY, planeX, planeY, map);
		SDL_RenderPresent(instance.renderer);
	}
	free_maze(map);
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}
