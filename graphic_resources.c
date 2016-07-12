#include <stdlib.h>

#include "graphic_resources.h"

int initialize_graphic_resources(struct GraphicResources *graphic_resources, 
	size_t max_images)
{
	graphic_resources->images = malloc(sizeof(SDL_Surface*) * max_images);
	if (graphic_resources->images == NULL)
		return 1;

	graphic_resources->textures = malloc(sizeof(SDL_Texture*) * max_images);
	if (graphic_resources->textures == NULL)
		return 2;

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

	if ((graphic_resources->textures = realloc(graphic_resources->textures,
		sizeof(SDL_Texture*) * max_images)) == NULL)
	{
		return 2;
	}

	graphic_resources->max_images = max_images;

	return 0;
}

int get_max_images(const struct GraphicResources *graphic_resources)
{
	return graphic_resources->max_images;
}

int load_image(struct GraphicResources *graphic_resources,
	SDL_Renderer *renderer, char *path)
{
	if (graphic_resources->image_count < graphic_resources->max_images)
	{
		SDL_Surface *image = SDL_LoadBMP(path);

		if (image == NULL)
			return 1;
		else
		{
			Uint32 transparent_rgb = SDL_MapRGB(image->format,
				TRANSPARENT_R, TRANSPARENT_G, TRANSPARENT_B);

			SDL_SetColorKey(image, SDL_TRUE, transparent_rgb);

			graphic_resources->images
				[graphic_resources->image_count] = image;

			SDL_Texture *texture = 
				SDL_CreateTextureFromSurface(renderer, image);
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

			graphic_resources->textures
				[graphic_resources->image_count] = texture;

			++graphic_resources->image_count;
		}
		
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
	SDL_DestroyTexture(graphic_resources->textures[image_id]);

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

int load_all_images(size_t image_count,
	struct GraphicResources *graphic_resources, SDL_Renderer *renderer)
{
	// TODO: Make this less-hardcoded. 
	char paths[5][25] = {"assets/background.bmp", "assets/board.bmp", 
		"assets/icon.bmp", "assets/star.bmp", "assets/moon.bmp"};

	int errors = 0;

	for (size_t i = 0; i < image_count; ++i)
		errors += load_image(graphic_resources, renderer, paths[i]);

	return errors;	
}

