#include "main.h"

int raycast(SDL_Renderer *renderer, float playerX, float playerY,
float playerDirX, float playerDirY, float planeX, float planeY, int **map)
{
	int x;

	/*cast rays*/
	for (x = 0; x < SCREEN_WIDTH; x++)
	{
		/*Calculate ray position and direction*/
		float cameraX = 2 * x / (float)SCREEN_WIDTH - 1; /*[-1, 1] range*/
		float rayDirX = playerDirX + planeX * cameraX;
		float rayDirY = playerDirY + planeY * cameraX;

		/*Calculate which grid the player is currently in*/
		int mapX = (int)playerX;
		int mapY = (int)playerY;

		/*Length of ray from current position to next x or y-side*/
		float sideDistX, sideDistY;

		/*Length of ray from one side to next x or y-side*/
		float deltaDistX = fabs(1 / rayDirX);
		float deltaDistY = fabs(1 / rayDirY);

		float perpWallDist;

		/*Step direction (which way to step in x or y direction)*/
		int stepX, stepY;
		int wallhit = 0; /*Was there a wall hit?*/
		int sideHit;    /*Was the wall hit on the X or Y side?*/

		/*Initial direction of step*/
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (playerX - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - playerX) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (playerY - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - playerY) * deltaDistY;
		}

		/*Perform DDA (Digital Differential Analysis)*/
		while (wallhit == 0)
		{
			/*Jump to next map square, X or Y direction*/
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				/*X side*/
				sideHit = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				/*Y side*/
				sideHit = 1;
			}

			/*Check if ray has hit a wall*/
			
			if (mapX < 0 || mapX >= MAP_SIZE || mapY < 0 || mapY >= MAP_SIZE)
			{
				/*Exit the loop if out of bounds*/
				break;
			}
			if (map[mapY][mapX] > 0)
			{
				wallhit = 1;
			}
		}

		/*Calculate distance to the point of wall hit*/
		if (sideHit == 0)
			perpWallDist = (mapX - playerX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - playerY + (1 - stepY) / 2) / rayDirY;

		/*Calculate height of the wall slice*/
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		/*Calculate lowest and highest pixel to fill in current stripe*/
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0)
		{
			drawStart = 0;
		}

		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
		{
			drawEnd = SCREEN_HEIGHT - 1;
		}

		/*draw ceiling*/
		SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
		SDL_RenderDrawLine(renderer, x, 0, x, drawStart);
		/*Set wall color (based on side hit)*/
		int colorIntensity = (int)(255 / (1 + perpWallDist * perpWallDist * 0.1));
		if (sideHit == 0)
			SDL_SetRenderDrawColor(renderer, colorIntensity, 0, 0, 255);  /*X side*/
		else
			SDL_SetRenderDrawColor(renderer, colorIntensity / 2, 0, 0, 255);  /*Y side, darker*/

		/*Draw the wall slice as a vertical line*/
		SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
		/*draw floor*/
		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 255);  /*Dark gray color for the floor*/
		SDL_RenderDrawLine(renderer, x, drawEnd, x, SCREEN_HEIGHT);
	}
	/*free_maze(map);*/
	return (0);
}
