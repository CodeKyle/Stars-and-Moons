#ifndef SLOT_DRAW_H
#define SLOT_DRAW_H

#include "SDL.h"

#include "slot.h" 

/*  Draws 'slot' on the 'image' surface, then draws said surface on the 'window'. */
void draw_slot(const struct slot *slot, SDL_Window *window, SDL_Surface *image);

/*  Draws all slot objects in 'cluster'. 'image_array' is an array with the desired
    surfaces to be drawn. This is provided to enable drawing a different image for
    a slot based on its "value" member. The 'cluster' will be drawn on the
    provided 'window'. */
void draw_slot_cluster(const struct slot cluster[], size_t cluster_size, SDL_Surface *image_array[], size_t image_array_size, SDL_Window *window);

#endif