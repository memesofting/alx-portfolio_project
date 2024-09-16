#include "main.h"

/**
 * draw_mini_map - draws maze map on game window
 * @renderer: SDL_Renderer instance
 * @player: player properties struct
 * @map: maze map array
 */

void draw_mini_map(SDL_Renderer *renderer, Player *player, int **map)
{
	int i, j, player_x, player_y, line_end_x, line_end_y;
	int offset_x, offset_y;

	/*Right corner with padding*/
	offset_x = SCREEN_WIDTH - (MAP_SIZE * MAP_SCALE) - 10;
	/*Top corner with padding*/
	offset_y = 10;

	/*Draw the maze grid*/
	for (i = 0; i < MAP_SIZE; i++)
	{
		for (j = 0; j < MAP_SIZE; j++)
		{
			if (map[i][j] == 1)  /*Wall*/
			{
				/*White for walls*/
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			else
			{
				/*Black for passages*/
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			}
			/*Draw the tile (scaled down for the mini-map)*/
			SDL_Rect tile = {offset_x + j * MAP_SCALE,
				offset_y + i * MAP_SCALE, MAP_SCALE, MAP_SCALE};
			SDL_RenderFillRect(renderer, &tile);
		}
	}
	/*Draw the player as a point*/
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  /*Green for the player*/
	player_x = offset_x + (int)(player->playerX * MAP_SCALE);
	player_y = offset_y + (int)(player->playerY * MAP_SCALE);
	SDL_RenderDrawPoint(renderer, player_x, player_y);
	/*Draw player's line of sight*/
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  /*Red for line of sight*/
	/*Extend the line 5 tiles*/
	line_end_x = player_x + (int)(player->playerDirX * 5 * MAP_SCALE);
	line_end_y = player_y + (int)(player->playerDirY * 5 * MAP_SCALE);
	SDL_RenderDrawLine(renderer, player_x, player_y, line_end_x, line_end_y);
}
