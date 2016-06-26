#include "graphic_resources.h"

#include <stdlib.h>

struct GraphicResources* create_graphic_resources()
{
	struct GraphicResources *new_graphic_resources = 
		malloc(sizeof(struct GraphicResources));

	if (new_graphic_resources != NULL)
	{
		new_graphic_resources->images = NULL;
		new_graphic_resources->image_count = 0;
	}

	return new_graphic_resources;
}

void initialize_image_array(struct GraphicResources *graphic_resources, 
	size_t image_count)
{
	graphic_resources->images = malloc(sizeof(SDL_Surface*) * image_count);
}

int load_image(struct GraphicResources *graphic_resources, char *file_path)
{
	SDL_Surface *test = SDL_LoadBMP(file_path);

	graphic_resources->images[0] = SDL_LoadBMP(file_path);

	//graphic_resources->image_count += 1;
}