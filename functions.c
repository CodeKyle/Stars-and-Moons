#include "constants.c"
#include "functions.h"

int get_device_resolution(int index, enum coord coord_type)
{
    int status;
    SDL_DisplayMode mode;
    
    status = SDL_GetDesktopDisplayMode(index, &mode);
    if (status < 0)
        return -1;
    
    if (coord_type == X_AXIS)
        return mode.w;
    else if (coord_type == Y_AXIS)
        return mode.h;
    else
        return -2;
}

int load_images(size_t size, SDL_Surface *image_array[], const char * const image_paths[])
{
    int errors = 0;
    size_t i;
    for (i = 0; i < size; ++i)
    {
        image_array[i] = SDL_LoadBMP(image_paths[i]);
        if (image_array[i] == NULL)
            ++errors;
        else
        {
            // Set the pixel color used for transparency. 
            Uint32 transparent_rgb = SDL_MapRGB(image_array[i]->format, TRANSPARENT_R, TRANSPARENT_G, TRANSPARENT_B);
            SDL_SetColorKey(image_array[i], SDL_TRUE, transparent_rgb);
        }
    }
    
    return errors;
}

int draw_surface(SDL_Window *window, SDL_Surface *surface, SDL_Rect area)
{
    if (area.w || area.h)
        return SDL_BlitScaled(surface, NULL, SDL_GetWindowSurface(window), &area);
    else
        return SDL_BlitSurface(surface, NULL, SDL_GetWindowSurface(window), &area);   
}

int mouse_over_area(int mouse_x, int mouse_y, int x, int y, int w, int h)
{
    if (mouse_x >= x && mouse_x <= x + w && mouse_y >= y && mouse_y <= y + h)
        return 1;
    else
        return 0;
}

