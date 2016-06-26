#include <stdlib.h>

#include "graphic_resources.h"

int initialize_graphic_resources(struct GraphicResources *graphic_resources, 
	size_t max_images)
{
	graphic_resources->images = malloc(sizeof(SDL_Surface*) * max_images);
	if (graphic_resources->images == NULL)
		return 1;

	graphic_resources->image_count = 0;
	graphic_resources->max_images = max_images;

	return 0;
}

int get_image_count(const struct GraphicResources *graphic_resources)
{
	return graphic_resources->image_count;
}

int set_max_images(struct GraphicResources *graphic_resources, size_t max_images)
{
	if ((graphic_resources->images = realloc(graphic_resources->images, 
		sizeof(SDL_Surface*) * max_images)) == NULL)
	{
		return 1;
	}

	graphic_resources->max_images = max_images;

	return 0;
}

int get_max_images(const struct GraphicResources *graphic_resources)
{
	return graphic_resources->max_images;
}

int load_image(struct GraphicResources *graphic_resources, char *path)
{
	if (graphic_resources->image_count < graphic_resources->max_images)
	{
		SDL_Surface *image = SDL_LoadBMP(path);
		if (image == NULL)
			return 1;
		else
			graphic_resources->images
				[graphic_resources->image_count++] = image;
		
		return 0;
	}
	else
	{
		return 2;
	}
}

int unload_image(struct GraphicResources *graphic_resources, size_t image_id)
{
	if (graphic_resources->images[image_id] == NULL)
		return 1;

	SDL_FreeSurface(graphic_resources->images[image_id]);
	graphic_resources->images[image_id] = NULL;
	--graphic_resources->image_count;

	return 0;
}

int unload_all_images(struct GraphicResources *graphic_resources)
{
	size_t image_count = graphic_resources->image_count;
	int errors = 0;

	for (size_t i = 0; i < image_count; ++i)
		errors += unload_image(graphic_resources, i);

	return errors;
}

int destroy_graphic_resources(struct GraphicResources *graphic_resources)
{
	int errors = unload_all_images(graphic_resources);

	free(graphic_resources->images);

	return errors;
}