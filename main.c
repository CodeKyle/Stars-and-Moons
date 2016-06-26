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

void update_surface(SDL_Window *window, SDL_Surface *surface, SDL_Rect area)
{
    SDL_BlitSurface(surface, &area, SDL_GetWindowSurface(window), &area);   
}

void update_background(SDL_Window *window, SDL_Surface *background, SDL_Rect pos)
{  
    SDL_BlitSurface(background, &pos, SDL_GetWindowSurface(window), &pos);
}

void draw_cursor(SDL_Window *window, SDL_Surface *cursor, SDL_Rect area)
{
    area.w = 32;
    area.h = 32;
    
    SDL_BlitSurface(cursor, NULL, SDL_GetWindowSurface(window), &area);
    //SDL_BlitScaled(cursor, NULL, SDL_GetWindowSurface(window), &area);   
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
    
    //int window_width = NATIVE_WIDTH;
    //int window_height = NATIVE_HEIGHT;
    
    SDL_Rect background_area = {0, 0, NATIVE_WIDTH, NATIVE_HEIGHT};

    update_surface(window, images[BACKGROUND], (SDL_Rect){0, 0, NATIVE_WIDTH, NATIVE_HEIGHT});
    
    
    SDL_Event event;
    SDL_Rect curs;
    
        SDL_Surface *cursor = images[ICON];
        int cursor_height = 32;
        int cursor_width = 32;
        
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
                SDL_Rect cursor_pos = {mouse_x, mouse_y, cursor_width, cursor_height};
                SDL_Rect background_pos = {mouse_x - 50, mouse_y - 50, cursor_width + 100, cursor_height + 100};
                
                //draw_cursor(window, cursor, cursor_pos);
                update_surface(window, images[BACKGROUND], (SDL_Rect){0, 0, NATIVE_WIDTH, NATIVE_HEIGHT});
                //update_surface(window, images[BACKGROUND], background_pos);        
                draw_cursor(window, cursor, cursor_pos);

                SDL_UpdateWindowSurface(window);

            }
            else if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {

                }
                
            }
        }
    }
    
    return 0;
}