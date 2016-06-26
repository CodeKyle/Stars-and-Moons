#ifndef GRAPHIC_RESOURCES_H
#define GRAPHIC_RESOURCES_H

#include "SDL.h"

struct GraphicResources
{
	SDL_Surface **images;
	size_t image_count;
};

struct GraphicResources* create_graphic_resources();

void initialize_image_array(struct GraphicResources *graphic_resources, 
	size_t image_count);

int resize_image_array(struct GraphicResources *graphic_resources, 
	size_t image_count);

int load_image(struct GraphicResources *graphic_resources, char *file_path);

void load_images(char **file_paths, size_t image_count);

#endif