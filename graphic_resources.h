#ifndef GRAPHIC_RESOURCES_H
#define GRAPHIC_RESOURCES_H

#include <stddef.h>

#include "SDL.h"

struct GraphicResources
{
	SDL_Surface **images;

	size_t image_count;
	size_t max_images;
};

/*	Initializes all variables in 'graphic_resources', providing enough room for
	'max_images' images. 
	Returns 0 if successful, otherwise 1.
	Note: Be sure to call destroy_graphic_resources() to prevent memory 
		leaks. */
int initialize_graphic_resources(struct GraphicResources *graphic_resources, 
	size_t max_images);

/*	Returns the current amount of images loaded into 'graphic_resources'. */
int get_image_count(const struct GraphicResources *graphic_resources);

/*	Sets the maximum amount of images 'graphics_resources' can hold to 
	'max_images'.
	Returns 0 if successfully able to increase the space for images, otherwise
		1 and storage space has not been changed. */
int set_max_images(struct GraphicResources *graphic_resources, 
	size_t max_images);

/*	Returns the maximum amount of images that can currently be loaded into
	'graphic_resources'. */
int get_max_images(const struct GraphicResources *graphic_resources);

/*	Loads the image located at 'path' into 'graphic_resources'. 
	Returns 0 if successful, otherwise:
		1 if the image was unable to be loaded.
		2 for an unspecified error. (TODO: Remove.) */
int load_image(struct GraphicResources *graphic_resources, char *path);

/*	Unloads the image within 'graphic_resources' containg 'image_id'.
	Returns 0 if successful, otherwise
		1 if the 'image_id' is out of range.
		2 if the image is NULL. */
int unload_image(struct GraphicResources *graphic_resources, size_t image_id);

/*	Unloads all currently loaded images within 'graphic_resources'. 
	Returns 0 if successful, otherwise an integer denoting the sum of error 
		codes obtained from unload_image() on each image. */ 
int unload_all_images(struct GraphicResources *graphic_resources);

/*	Destroy 'graphic_resources', freeing all allocated memory and images
	within. */
int destroy_graphic_resources(struct GraphicResources *graphic_resources);

#endif