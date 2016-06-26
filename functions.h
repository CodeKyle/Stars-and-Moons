#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "SDL.h"

/*  Simple enum used in some functions to obtain either an x-coordinate
    or a y-coordinate. */
enum coord {X_AXIS, Y_AXIS};

/*  Returns either the width or the height of the display device indicated
    by 'index'. The value for 'coord_type' must be either X_AXIS for the
    width or Y_AXIS for the height. If the display device could not be
    checked, -1 is returned. If an invalid 'coord_type' is provided, -2
    is returned. */
int get_device_resolution(int index, enum coord coord_type);

/*  Loads 'size' amount of images into 'image_array' using the file path
    from 'image_paths'. Returns the amount of images that were unsuccessfully
    loaded, or 0 if all images were loaded. */
int load_images(size_t size, SDL_Surface *image_array[], const char * const image_paths[]);

/*  If a width or height was specified for 'area', then scale 'surface' to fit
    those dimensions. Otherwise, just blit the 'surface' at the provided
    (x, y) coordinates on the surface of 'window'. Returns a negative value
    if the blit is unsuccessful, or 0 if it was successful. */
int draw_surface(SDL_Window *window, SDL_Surface *surface, SDL_Rect area);

/*  Checks if ('mouse_x', 'mouse_y') is within the bounds of the following
    area coordinates. Returns 1 if true, otherwise 0. */
int mouse_over_area(int mouse_x, int mouse_y, int x, int y, int w, int h);

#endif