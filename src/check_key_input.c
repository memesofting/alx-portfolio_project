#include "main.h"

int check_key(void)
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
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					loop = 0;
				}
				break;
			default:
				break;
		}
	}
	return (loop);
}
