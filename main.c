#include "SDL.h"
#include <stdio.h>

#define WINDOW_TITLE "Stars and Moons"
#define NATIVE_WIDTH 960
#define NATIVE_HEIGHT 640

#define IMAGE_COUNT 5

#define BACKGROUND 0
#define STAR 1
#define MOON 2
#define BOARD 3
#define ICON 4

#define TRANSPARENT_R 255
#define TRANSPARENT_G 0
#define TRANSPARENT_B 255

#define CURSOR_WIDTH 100
#define CURSOR_HEIGHT 100

enum coord {X_AXIS, Y_AXIS};

/*  Returns either the width or the height of the display device indicated
    by 'index'. The value for 'coord_type' must be either X_AXIS for the
    width or Y_AXIS for the height. If the display device could not be
    checked, -1 is returned. If an invalid 'coord_type' is provided, -2
    is returned. */
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

/*  Loads 'size' amount of images into 'image_array' using the file path
    from 'image_paths'. Returns the amount of images that were unsuccessfully
    loaded, or 0 if all images were loaded. */
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

/*  If a width or height was specified for 'area', then scale 'surface' to fit
    those dimensions. Otherwise, just blit the 'surface' at the provided
    (x, y) coordinates on the surface of 'window'. Returns a negative value
    if the blit is unsuccessful, or 0 if it was successful. */
int update_surface(SDL_Window *window, SDL_Surface *surface, SDL_Rect area)
{
    if (area.w || area.h)
        return SDL_BlitScaled(surface, NULL, SDL_GetWindowSurface(window), &area);
    else
        return SDL_BlitSurface(surface, NULL, SDL_GetWindowSurface(window), &area);   
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    
    int x, y;
    x = get_device_resolution(0, X_AXIS);
    y = get_device_resolution(0, Y_AXIS);
    if (x && y)
        printf("Display device resolution is %d by %d\n", x, y);
        
    const char * const image_paths[] = {"background.bmp", "star.bmp", "moon.bmp", "board.bmp", "icon.bmp"};
    SDL_Surface *images[IMAGE_COUNT];
    int errors = load_images(IMAGE_COUNT, images, image_paths);
    if (errors)
        printf("%d errors in load_images()\n", errors);    
        
    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          NATIVE_WIDTH, NATIVE_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_ShowWindow(window);
    
    int window_width = NATIVE_WIDTH;
    int window_height = NATIVE_HEIGHT;
    
    SDL_Rect background_pos = {0, 0, window_width, window_height};
    update_surface(window, images[BACKGROUND], background_pos);   
    
    SDL_Surface *cursor = images[MOON];
    SDL_Rect cursor_pos;  
        
    SDL_Event event;
    while (1)
    {        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SDL_Quit();
                return 0;
            }
            else if (event.type == SDL_MOUSEMOTION)
            {
                int mouse_x = 0, mouse_y = 0;
                SDL_GetMouseState(&mouse_x, &mouse_y);
                cursor_pos = (SDL_Rect){mouse_x, mouse_y, CURSOR_WIDTH, CURSOR_HEIGHT};
                
                update_surface(window, images[BACKGROUND], background_pos);
                update_surface(window, images[MOON], cursor_pos);

                SDL_UpdateWindowSurface(window);

            }
            else if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    SDL_GetWindowSize(window, &window_width, &window_height);
                    background_pos = (SDL_Rect){0, 0, window_width, window_height};
                    
                    update_surface(window, images[BACKGROUND], background_pos);
                    update_surface(window, images[MOON], cursor_pos);
    
                    SDL_UpdateWindowSurface(window);
                }
                
            }
        }
    }
    
    return 0;
}