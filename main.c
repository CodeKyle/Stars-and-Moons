#include "SDL.h"
#include <stdio.h>

#include "constants.c"
#include "functions.h"
#include "matrix.h"
#include "slot.h"
#include "slot_draw.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    
    //  Get the resolution of the main output device.
    int x, y;
    x = get_device_resolution(0, X_AXIS);
    y = get_device_resolution(0, Y_AXIS);
    if (!x || !y)
    {
        printf("Unable to obtain device resolution. Terminating...\n");
        return 1;
    }
    
    // Load all the images to be used. 
    const char * const image_paths[] = {"assets//background.bmp", "assets//star.bmp", "assets//moon.bmp", "assets//board.bmp", "assets//icon.bmp"};
    SDL_Surface *images[IMAGE_COUNT];
    int errors = load_images(IMAGE_COUNT, images, image_paths);
    if (errors)
    {
        printf("%d images could not be loaded. Terminating...\n", errors);
        return 2;
    }
        
    // Set up and show the game window.    
    int window_width = NATIVE_WIDTH;
    int window_height = NATIVE_HEIGHT;
    SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          window_width, window_height, SDL_WINDOW_RESIZABLE);
    SDL_ShowWindow(window);  

    // Draw the background image.
    SDL_Rect background_pos = {0, 0, window_width, window_height};
    draw_surface(window, images[BACKGROUND], background_pos);   
    
    // Set up the cursor.
    SDL_Rect cursor_pos;  
    SDL_Surface *cursor = images[STAR];

    // Set up the matrix for the game board.
    int board[BOARD_WIDTH][BOARD_HEIGHT];
    clear_matrix(SLOT_SENTINEL_VALUE, BOARD_WIDTH, BOARD_HEIGHT, board);
    
    // Set up the slots for the game board.
    struct slot board_slots[BOARD_WIDTH * BOARD_HEIGHT];
    SDL_Rect board_pos = (SDL_Rect){0, 0, NATIVE_SLOT_CLUSTER_WIDTH , NATIVE_SLOT_CLUSTER_HEIGHT}; // Don't care about x or y because the board will be centered.
    board_pos.x = window_width / 2 - board_pos.w / 2;
    board_pos.y = window_height / 2 - board_pos.h / 2,
    initialize_slot_cluster(board_slots, BOARD_WIDTH, BOARD_HEIGHT, SLOT_SENTINEL_VALUE, board_pos.x, board_pos.y,
                            board_pos.w, board_pos.h);
    
    // Draw the game board.
    draw_surface(window, images[BOARD], board_pos );    
    
    // Update the window.
    SDL_UpdateWindowSurface(window);

    // Additional tracking variables.
    int mouse_x = 0, mouse_y = 0;    
    int player_turn = 1;    
    SDL_Event event;
    
    // Game loop.
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
                // Get the new mouse position and update the cursor's draw area.
                SDL_GetMouseState(&mouse_x, &mouse_y);
                cursor_pos = (SDL_Rect){mouse_x, mouse_y, CURSOR_WIDTH, CURSOR_HEIGHT};
                
                // Re-draw all the images.
                draw_surface(window, images[BACKGROUND], background_pos);
                draw_surface(window, images[BOARD], board_pos );                
                draw_slot_cluster(board_slots, BOARD_WIDTH * BOARD_HEIGHT, images, IMAGE_COUNT, window);
                draw_surface(window, cursor, cursor_pos);            

                // Update the window.
                SDL_UpdateWindowSurface(window);
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                // If mouse is over the game board...
                if (mouse_over_area(mouse_x, mouse_y, board_pos.x, board_pos.y, board_pos.w, board_pos.h))
                {
                    // ...get the slot it is over.
                    struct slot* slot_under_mouse = get_slot_at_pos(board_slots, BOARD_WIDTH * BOARD_HEIGHT, mouse_x, mouse_y);
                    
                    // Just make sure the slot isn't NULL before trying to check it.
                    if (slot_under_mouse != NULL)
                    {
                        // Make sure the slot wasn't already claimed by another player.
                        if (slot_under_mouse->value == SLOT_SENTINEL_VALUE)
                        {
                            // Set the 'value' of the slot to be equal to the player's number.
                            slot_under_mouse->value = player_turn;
                            
                            // Get the x and y positions of the selected slot. 
                            int slot_x = get_slot_coordinate(X_AXIS, slot_under_mouse, board_slots, BOARD_WIDTH, BOARD_HEIGHT);
                            int slot_y = get_slot_coordinate(Y_AXIS, slot_under_mouse, board_slots, BOARD_WIDTH, BOARD_HEIGHT);
                            
                            // Place the player's value at said position in the board matrix.
                            set_matrix_value(player_turn, slot_x, slot_y, BOARD_WIDTH, BOARD_HEIGHT, board);
                            
                            // If a player has now won, fill the board with their piece.
                            // TODO: Make something more exciting happen, and provide a way to restart the game.
                            if (check_victory(player_turn, slot_x, slot_y, BOARD_WIDTH, BOARD_HEIGHT, board))
                            {
                                set_slot_cluster_value(board_slots, BOARD_WIDTH * BOARD_HEIGHT, player_turn);
                            }
                            
                            // Move to the other player.
                            if (player_turn == 1)
                            {
                                cursor = images[MOON];                                
                                player_turn = 2;
                            }
                            else if (player_turn == 2)
                            {                                                             
                                cursor = images[STAR];
                                player_turn = 1;
                            }
                
                        }
                    }
                    
                    draw_surface(window, images[BACKGROUND], background_pos);
                    draw_surface(window, images[BOARD], board_pos );                
                    draw_slot_cluster(board_slots, BOARD_WIDTH * BOARD_HEIGHT, images, IMAGE_COUNT, window);                  

                    draw_surface(window, cursor, cursor_pos);
                    SDL_UpdateWindowSurface(window);
                }
            }
            else if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    // Get the new window size.
                    SDL_GetWindowSize(window, &window_width, &window_height);
                    
                    // Update the background image's area.
                    background_pos = (SDL_Rect){0, 0, window_width, window_height};
                    
                    // Update the board image's area.
                    board_pos = (SDL_Rect){ window_width / 2 - board_pos.w / 2,
                                            window_height / 2 - board_pos.h / 2,
                                            board_pos.w, board_pos.h};
                                              
                    // Update the slot cluster's areas.
                    set_slot_cluster_area(  board_slots, BOARD_WIDTH, BOARD_HEIGHT,
                                            board_pos.x, board_pos.y,
                                            board_pos.w, board_pos.h);

                    // Re-draw all the images.
                    draw_surface(window, images[BACKGROUND], background_pos);                   
                    draw_surface(window, images[BOARD], board_pos );
                    draw_slot_cluster(board_slots, BOARD_WIDTH * BOARD_HEIGHT, images, IMAGE_COUNT, window);
                    draw_surface(window, images[MOON], cursor_pos);              
    
                    // Update the window.
                    SDL_UpdateWindowSurface(window);
                }
                
            }
        }
    }
    
    return 0;
}