#include "main.h"

int check_key(float *playerX, float *playerY, float *playerDirX,
float *playerDirY, float *planeX, float *planeY)
{
	int loop;
	float speed, rotspeed;
	SDL_Event event;

	loop = 1;
	speed = 0.2f;
	rotspeed = 0.2f;
    while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				loop = 0;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					loop = 0;
				}
				if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_UP)
				{
					*playerX += *playerDirX * speed;
					*playerY += *playerDirY * speed;
				}
				if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_RIGHT)
				{
					float oldDirX = *playerDirX;
                    *playerDirX = *playerDirX * cos(-rotspeed) - *playerDirY * sin(-rotspeed);
                    *playerDirY = oldDirX * sin(-rotspeed) + *playerDirY * cos(-rotspeed);

                    float oldPlaneX = *planeX;
                    *planeX = *planeX * cos(-rotspeed) - *planeY * sin(-rotspeed);
                    *planeY = oldPlaneX * sin(-rotspeed) + *planeY * cos(-rotspeed);
				}
				if (event.key.keysym.sym == SDLK_s || event.key.keysym.sym == SDLK_DOWN)
				{
					*playerX -= *playerDirX * speed;
					*playerY -= *playerDirY * speed;
				}
				if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_LEFT)
				{
					float oldDirX = *playerDirX;
                    *playerDirX = *playerDirX * cos(rotspeed) - *playerDirY * sin(rotspeed);
                    *playerDirY = oldDirX * sin(rotspeed) + *playerDirY * cos(rotspeed);

                    float oldPlaneX = *planeX;
                    *planeX = *planeX * cos(rotspeed) - *planeY * sin(rotspeed);
                    *planeY = oldPlaneX * sin(rotspeed) + *planeY * cos(rotspeed);
				}
				
				break;
			default:
				break;
		}
	}
	return (loop);
}
