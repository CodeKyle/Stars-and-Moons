#include "constants.c"
#include "functions.h"
#include "slot_draw.h"

void draw_slot(const struct slot *slot, SDL_Window *window, SDL_Surface *image)
{    
    SDL_Rect area;
    area.x = slot->x_pos;
    area.y = slot->y_pos;
    area.w = slot->width;
    area.h = slot->height;

    draw_surface(window, image, area);
}

void draw_slot_cluster(const struct slot cluster[], size_t cluster_size, SDL_Surface *image_array[], size_t image_array_size, SDL_Window *window)
{
    size_t i;
    for (i = 0; i < cluster_size; ++i)
    {
        // Check to ensure the value of the slot is meaningful and within bounds of the array.
        if (cluster[i].value != SLOT_SENTINEL_VALUE && cluster[i].value >= 0 && cluster[i].value < image_array_size)
            draw_slot(&cluster[i], window, image_array[cluster[i].value]);
    }
}
