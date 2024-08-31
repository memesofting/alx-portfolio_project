#include "main.h"

/**
 * main - main function for running game
 * Return: 0 on success
 */

int main(void)
{
	SDL_Event event;
	SDL_Instance instance;
	int game_loop;
	float playerX, playerY, planeX, planeY, playerDirX, playerDirY;

	playerX = 3.0f;
	playerY = 3.0f;
	playerDirX = -1.0f;
	playerDirY = 0.0f;
	planeX = 0.0f;  /*For FOV projection*/
	planeY = 0.66f; /*FOV set to 66°*/

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
		raycast(instance.renderer, playerX, playerY, playerDirX, playerDirY, planeX, planeY);
		SDL_RenderPresent(instance.renderer);
	}
	SDL_DestroyRenderer(instance.renderer);
	SDL_DestroyWindow(instance.window);
	SDL_Quit();
	return (0);
}

int raycast(SDL_Renderer *renderer, float playerX, float playerY, float playerDirX, float playerDirY, float planeX, float planeY)
{
	int x;

	int map[8][8] = {
    {1, 1, 0, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0},
    {1, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 1, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 1, 0}
	};
	/*cast rays*/

	for (x = 0; x < SCREEN_WIDTH; x++) {
    // Calculate ray position and direction
    float cameraX = 2 * x / (float)SCREEN_WIDTH - 1; // [-1, 1] range
    float rayDirX = playerDirX + planeX * cameraX;
    float rayDirY = playerDirY + planeY * cameraX;

    // Calculate which grid the player is currently in
    int mapX = (int)playerX;
    int mapY = (int)playerY;

    // Length of ray from current position to next x or y-side
    float sideDistX, sideDistY;

    // Length of ray from one side to next x or y-side
    float deltaDistX = fabs(1 / rayDirX);
    float deltaDistY = fabs(1 / rayDirY);

    float perpWallDist;

    // Step direction (which way to step in x or y direction)
    int stepX, stepY;
    int hit = 0; // Was there a wall hit?
    int side;    // Was the wall hit on the X or Y side?

    // Initial direction of step
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

    // Perform DDA (Digital Differential Analysis)
    while (hit == 0) {
        // Jump to next map square, X or Y direction
        if (sideDistX < sideDistY) {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0; // X side
        } else {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1; // Y side
        }

        // Check if ray has hit a wall
        if (map[mapX][mapY] > 0) hit = 1;
    }

    // Calculate distance to the point of wall hit
    if (side == 0)
        perpWallDist = (mapX - playerX + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - playerY + (1 - stepY) / 2) / rayDirY;

    // Calculate height of the wall slice
    int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

    // Calculate lowest and highest pixel to fill in current stripe
    int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (drawStart < 0) drawStart = 0;
    int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
    if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

    // Set wall color (based on side hit)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
    if (side == 1) SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255); // Darker for Y side

    // Draw the wall slice as a vertical line
    SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
	}
	return (0);
}
