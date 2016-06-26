#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include "graphic_resources.h"

/* create/destroy window/graphicsresources, 
void drawWindow(GraphicsResources *resources, Window *window, GameState *game); 
a function that, for a given Window, finds out whether a given mouse position is 
inside a slot. */

struct Window
{
	float x_pos, y_pos, width, height;
	char *window_title;
	SDL_Window* window;
};


struct Window *create_window(char* title, float x_pos, float y_pos, 
	float width, float height);

void set_window_dimensions(float x_pos, float y_pos, 
	float width, float height);

void set_window_position(struct Window *window, float x_pos, float y_pos);

void set_window_size(struct Window *window, float width, float height);

void draw(struct Window *window, struct GraphicResources *gr);

void destroy_window(struct Window* window);

#endif