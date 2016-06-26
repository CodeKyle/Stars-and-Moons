#include <stdlib.h>

#include "window.h"

struct Window *create_window(char* title, float x_pos, float y_pos, 
	float width, float height)
{
	struct Window *new_window = malloc(sizeof(struct Window));

	new_window->window_title = title;

	new_window->window = SDL_CreateWindow(title, x_pos, y_pos, 
		width, height, 0);

	return new_window;
}

void set_window_position(struct Window *window, float x_pos, float y_pos)
{
	SDL_SetWindowPosition(window->window, x_pos, y_pos);
}

void set_window_size(struct Window *window, float width, float height)
{
	SDL_SetWindowSize(window->window, width, height);
}

void draw(struct Window *window, struct GraphicResources *gr)
{
	SDL_BlitSurface(gr->images[0], NULL, 
		SDL_GetWindowSurface(window->window), NULL);

	SDL_UpdateWindowSurface(window->window);
}

void destroy_window(struct Window* window)
{
	SDL_DestroyWindow(window->window);
	free(window);
}