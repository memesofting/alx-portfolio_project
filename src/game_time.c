#include "main.h"

/* Render the timer on the screen */
void render_timer(SDL_Renderer *renderer, TTF_Font *font, int remaining_time)
{
	/* White color */
	SDL_Color textColor = {255, 255, 255, 255};
	char time_str[20];
	snprintf(time_str, sizeof(time_str), "Time: %d", remaining_time / 1000);

	SDL_Surface *textSurface = TTF_RenderText_Solid(font, time_str, textColor);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	/* Position of the timer */
	SDL_Rect textRect = {10, 10, textSurface->w, textSurface->h};
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void game_over(SDL_Renderer *renderer, TTF_Font *font)
{
	/* White color */
	SDL_Color textColor = {255, 255, 255, 255};
	char time_str[20];
	snprintf(time_str, sizeof(time_str), "Game Over");

	SDL_Surface *textSurface = TTF_RenderText_Solid(font, time_str, textColor);
	SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	/* Position of the game over text */
	SDL_Rect textRect = {(SCREEN_WIDTH - textSurface->w) / 2,
		(SCREEN_HEIGHT - textSurface->h) / 2, textSurface->w, textSurface->h};
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}
