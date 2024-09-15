#include "main.h"

/* Function to calculate the direction and setup of the ray */
void calculateRayDirection(int x, float *rayDirX, float *rayDirY,
		float playerDirX, float playerDirY, float planeX, float planeY)
{
	float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
	*rayDirX = playerDirX + planeX * cameraX;
	*rayDirY = playerDirY + planeY * cameraX;
}

/* Function to calculate the side distances */
void calculateSideDist(float playerX, float playerY, int mapX, int mapY,
		float rayDirX, float rayDirY, float *sideDistX, float *sideDistY,
		float deltaDistX, float deltaDistY, int *stepX, int *stepY)
{
	if (rayDirX < 0)
	{
		*stepX = -1;
		*sideDistX = (playerX - mapX) * deltaDistX;
	}
	else
	{
		*stepX = 1;
		*sideDistX = (mapX + 1.0 - playerX) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		*stepY = -1;
		*sideDistY = (playerY - mapY) * deltaDistY;
	}
	else
	{
		*stepY = 1;
		*sideDistY = (mapY + 1.0 - playerY) * deltaDistY;
	}
}

/* Perform DDA to find wall hits */
int performDDA(int *mapX, int *mapY, float *sideDistX, float *sideDistY,
		float deltaDistX, float deltaDistY, int *sideHit,
		int stepX, int stepY, int **map)
{
	int wallHit = 0;

	while (wallHit == 0)
	{
		/* Jump to next map square */
		if (*sideDistX < *sideDistY)
		{
			*sideDistX += deltaDistX;
			*mapX += stepX;
			*sideHit = 0;  /* X-side */
		}
		else
		{
			*sideDistY += deltaDistY;
			*mapY += stepY;
			*sideHit = 1;  /* Y-side */
		}
		/* Check for collision with a wall or boundary */
		if (*mapX < 0 || *mapX >= MAP_SIZE || *mapY < 0 || *mapY >= MAP_SIZE)
		{
			break;  /* Out of bounds */
		}
		if (map[*mapY][*mapX] > 0)
		{
			wallHit = 1;
		}
	}
	return (wallHit);
}

/* Render the walls, ceiling, and floor */
void renderSlice(SDL_Renderer *renderer, int x, int drawStart, int drawEnd,
		int sideHit, float perpWallDist)
{
	/* Draw ceiling */
	SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);  /* Sky blue */
	SDL_RenderDrawLine(renderer, x, 0, x, drawStart);

	/* Set wall color based on side */
	int colorIntensity = (int)(255 / (1 + perpWallDist * perpWallDist * 0.1));

	if (sideHit == 0)
	/* X side */
		SDL_SetRenderDrawColor(renderer, colorIntensity, 0, 0, 255);
	else
	/* Y side */
		SDL_SetRenderDrawColor(renderer, colorIntensity / 2, 0, 0, 255);

	/* Draw the wall slice */
	SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
	/* Draw floor */
	SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);  /* Dark gray */
	SDL_RenderDrawLine(renderer, x, drawEnd, x, SCREEN_HEIGHT);
}

/* Main raycasting function */
int raycast(SDL_Renderer *renderer, float playerX, float playerY,
		float playerDirX, float playerDirY,
		float planeX, float planeY, int **map)
{
	int x, stepX, stepY, sideHit;

	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		float rayDirX, rayDirY, sideDistX, sideDistY, deltaDistX, deltaDistY;

		calculateRayDirection(x, &rayDirX, &rayDirY, playerDirX,
				playerDirY, planeX, planeY);
		int mapX = (int)playerX;
		int mapY = (int)playerY;

		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		calculateSideDist(playerX, playerY, mapX, mapY, rayDirX, rayDirY,
				&sideDistX, &sideDistY, deltaDistX, deltaDistY, &stepX, &stepY);
		if (performDDA(&mapX, &mapY, &sideDistX, &sideDistY, deltaDistX,
					deltaDistY, &sideHit, stepX, stepY, map))
		{
			float perpWallDist = (sideHit == 0) ? (mapX - playerX + (1 - stepX) / 2)
				/ rayDirX : (mapY - playerY + (1 - stepY) / 2) / rayDirY;

			int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
			int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;

			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

			if (drawEnd >= SCREEN_HEIGHT)
				drawEnd = SCREEN_HEIGHT - 1;
			renderSlice(renderer, x, drawStart, drawEnd, sideHit, perpWallDist);
		}
	}
	return (0);
}
