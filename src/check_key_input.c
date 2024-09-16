#include "main.h"

/**
 * check_input - checks for player input during gameplay
 * @player: player properties struct
 * Return: loop value on success
 */

int check_input(Player *player)
{
	int loop;
	SDL_Event event;

	loop = 1;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				loop = 0;
				break;
			case SDL_KEYDOWN:
				loop = check_key(&event, player);
				break;
			case SDL_MOUSEMOTION:
				check_mouse(&event, player);
				break;
			default:
				break;
		}
	}
	return (loop);
}

/**
 * check_key - checks for keyboard input
 * @event: SDL event listener
 * @player: player properties struct
 * Return: 0 for esc key else 1
 */

int check_key(SDL_Event *event, Player *player)
{
	float speed;

	speed = 0.02f;
	switch (event->type)
	{
		case SDL_KEYDOWN:
			if (event->key.keysym.sym == SDLK_ESCAPE)
			{
				return (0);
			}
			if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_UP)
			{
				player->playerX += player->playerDirX * speed;
				player->playerY += player->playerDirY * speed;
			}
			if (event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_LEFT)
			{
				player->playerX -= player->planeX * speed;
				player->playerY -= player->planeY * speed;
			}
			if (event->key.keysym.sym == SDLK_s || event->key.keysym.sym == SDLK_DOWN)
			{
				player->playerX -= player->playerDirX * speed;
				player->playerY -= player->playerDirY * speed;
			}
			if (event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_RIGHT)
			{
				player->playerX += player->planeX * speed;
				player->playerY += player->planeY * speed;
			}
			break;
	}
	return (1);
}

/**
 * check_mouse - checks for mouse movement
 * @event: SDL event listener
 * @player: player properties struct
 */

void check_mouse(SDL_Event *event, Player *player)
{
	float rotspeed, oldDirX, oldPlaneX;
	int xrel;

	rotspeed = 0.01f;
	xrel = event->motion.xrel;
	if (xrel > 0)
	{
		/*Rotate the player's direction right based on the relative mouse movement*/
		oldDirX = player->playerDirX;
		player->playerDirX = player->playerDirX * cos(-rotspeed * xrel) -
			player->playerDirY * sin(-rotspeed * xrel);
		player->playerDirY = oldDirX * sin(-rotspeed * xrel) +
			player->playerDirY * cos(-rotspeed * xrel);

		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(-rotspeed * xrel) -
			player->planeY * sin(-rotspeed * xrel);
		player->planeY = oldPlaneX * sin(-rotspeed * xrel) +
			player->planeY * cos(-rotspeed * xrel);
	}
	if (xrel < 0)
	{
		/*Rotate the player's direction left based on the relative mouse movement*/
		oldDirX = player->playerDirX;
		player->playerDirX = player->playerDirX * cos(rotspeed * -xrel) -
			player->playerDirY * sin(rotspeed * -xrel);
		player->playerDirY = oldDirX * sin(rotspeed * -xrel) +
			player->playerDirY * cos(rotspeed * -xrel);

		oldPlaneX = player->planeX;
		player->planeX = player->planeX * cos(rotspeed * -xrel) -
			player->planeY * sin(rotspeed * -xrel);
		player->planeY = oldPlaneX * sin(rotspeed * -xrel) +
			player->planeY * cos(rotspeed * -xrel);
	}
}
