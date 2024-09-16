#include "main.h"

/**
 * init_player - initialises player properties
 * Return: pointer to Player struct
 */

Player *init_player(void)
{
	Player *player;

	player = malloc(sizeof(Player));
	if (player == NULL)
	{
		return (NULL);
	}
	player->playerX = 3.0f;
	player->playerY = 4.0f;
	player->playerDirX = -1.0f;
	player->playerDirY = 0.0f;
	player->planeY = 0.66f;
	player->planeX = 0.0f;
	return (player);
}
