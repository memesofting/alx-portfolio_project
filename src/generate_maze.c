#include "main.h"

/**
 * init_maze - initializes the maze array
 * @maze: maze array
 */

void init_maze(int **maze)
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

/**
 * is_valid - checks point in array
 * @x: horizontal array value
 * @y: vertical array value
 * @maze: maze array
 * Return: 0 on success
 */

int is_valid(int x, int y, int **maze)
{
	return (x >= 0 && x < MAP_SIZE &&
			y >= 0 && y < MAP_SIZE && maze[y][x] == 0);
}

/**
 * generate_maze - generates the maze map
 * @x: x array value
 * @y: y array value
 * @maze: maze map array
 */

void generate_maze(int x, int y, int **maze)
{
	/*nx and ny are neighbor grids*/
	int i, r, temp, nx, ny;
	/*passage movement direction*/
	int dx[4] = {0, 0, -1, 1};
	int dy[4] = {-1, 1, 0, 0};
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

/**
 * random_maze - generates random maze
 * Return: pointer to maze on success
 */

int **random_maze(void)
{
	int **maze;
	int i, j;

	maze = malloc(MAP_SIZE * sizeof(int *));
	if (maze == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < MAP_SIZE; i++)
	{
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
	/*Initialize and generate the maze*/
	init_maze(maze);
	generate_maze(1, 1, maze);
	return (maze);
}
