#include "main.h"

int check_input(float *playerX, float *playerY, float *playerDirX,
		float *playerDirY, float *planeX, float *planeY)
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
				loop = check_key(&event, playerX, playerY,
						playerDirX, playerDirY, planeX, planeY);
				break;
			case SDL_MOUSEMOTION:
				check_mouse(&event, playerDirX, playerDirY, planeX, planeY);
				break;
			default:
				break;
		}
	}
	return (loop);
}

int check_key(SDL_Event *event, float *playerX, float *playerY,
		float *playerDirX, float *playerDirY, float *planeX, float *planeY)
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
				*playerX += *playerDirX * speed;
				*playerY += *playerDirY * speed;
			}
			if (event->key.keysym.sym == SDLK_a || event->key.keysym.sym == SDLK_LEFT)
			{
				*playerX -= *planeX * speed;
				*playerY -= *planeY * speed;
			}
			if (event->key.keysym.sym == SDLK_s || event->key.keysym.sym == SDLK_DOWN)
			{
				*playerX -= *playerDirX * speed;
				*playerY -= *playerDirY * speed;
			}
			if (event->key.keysym.sym == SDLK_d || event->key.keysym.sym == SDLK_RIGHT)
			{
				*playerX += *planeX * speed;
				*playerY += *planeY * speed;
			}
			break;
	}
	return (1);
}

void check_mouse(SDL_Event *event, float *playerDirX,
		float *playerDirY, float *planeX, float *planeY)
{
	float rotspeed, oldDirX, oldPlaneX;
	int xrel;

	rotspeed = 0.01f;
	xrel = event->motion.xrel;
	if (xrel > 0)
	{
		/*Rotate the player's direction right based on the relative mouse movement*/
		oldDirX = *playerDirX;
		*playerDirX = *playerDirX * cos(-rotspeed * xrel) -
			*playerDirY * sin(-rotspeed * xrel);
		*playerDirY = oldDirX * sin(-rotspeed * xrel) +
			*playerDirY * cos(-rotspeed * xrel);

		oldPlaneX = *planeX;
		*planeX = *planeX * cos(-rotspeed * xrel) -
			*planeY * sin(-rotspeed * xrel);
		*planeY = oldPlaneX * sin(-rotspeed * xrel) +
			*planeY * cos(-rotspeed * xrel);
	}
	if (xrel < 0)
	{
		/*Rotate the player's direction left based on the relative mouse movement*/
		oldDirX = *playerDirX;
		*playerDirX = *playerDirX * cos(rotspeed * -xrel) -
			*playerDirY * sin(rotspeed * -xrel);
		*playerDirY = oldDirX * sin(rotspeed * -xrel) +
			*playerDirY * cos(rotspeed * -xrel);

		oldPlaneX = *planeX;
		*planeX = *planeX * cos(rotspeed * -xrel) -
			*planeY * sin(rotspeed * -xrel);
		*planeY = oldPlaneX * sin(rotspeed * -xrel) +
			*planeY * cos(rotspeed * -xrel);
	}
}
