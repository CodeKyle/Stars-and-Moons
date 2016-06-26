#include <stdio.h>

#include "SDL.h"

#include "constants.h"
#include "game_state.h"
#include "graphic_resources.h"
#include "matrix.h"
#include "window.h"

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return 1;

	struct Window window;
	
	if (initialize_window(&window) != 0)
		return 2;

	set_window_title(&window, "Stars and Moons");
	set_window_dimensions(&window, 50, 50, 640, 640, 1.75);

	struct GraphicResources graphic_resources;

	// Provide room for five images.
	if (initialize_graphic_resources(&graphic_resources, 5) != 0)
		return 3;

	Uint32 transparent_rgb; // Transparent pixel color.

	// TODO: Move these out of main.
	load_image(&graphic_resources, "assets/background.bmp");
	load_image(&graphic_resources, "assets/board.bmp");
	load_image(&graphic_resources, "assets/icon.bmp");

	load_image(&graphic_resources, "assets/star.bmp");
	transparent_rgb = SDL_MapRGB(graphic_resources.images[3]->format, 
		TRANSPARENT_R, TRANSPARENT_G, TRANSPARENT_B);
	SDL_SetColorKey(graphic_resources.images[3], SDL_TRUE, transparent_rgb);

	load_image(&graphic_resources, "assets/moon.bmp");
	transparent_rgb = SDL_MapRGB(graphic_resources.images[4]->format, 
		TRANSPARENT_R, TRANSPARENT_G, TRANSPARENT_B);
	SDL_SetColorKey(graphic_resources.images[4], SDL_TRUE, transparent_rgb); 

	// Initialize game data.
	struct GameState game_state;
	if (initialize_game_state(&game_state, BOARD_ROWS, BOARD_COLS) != 0)
		return 4;

	set_game_player(&game_state, STAR);

	// Set the initial values on the board.
	set_all_game_matrix_values(&game_state, GAME_STATE_SENTINEL);

	draw_window(&window, &game_state, &graphic_resources);

	SDL_Event event;
	int run_game = 1;
	
	while (run_game)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				run_game = 0;

			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					int window_width, window_height;

					SDL_GetWindowSize(window.window, 
						&window_width, &window_height);

					set_window_size(&window, window_width, window_height);
					draw_window(&window, &game_state, &graphic_resources);
				}

			}
		
			else if(event.type == SDL_MOUSEMOTION)
			{				
				draw_window(&window, &game_state, &graphic_resources);
			}

			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				/*	Check if the mouse is over a game piece and if it is 
					available. If so, claim it and check for a victory. */
				int i = DIMENSION_SENTINEL, j = DIMENSION_SENTINEL;

				i = get_game_piece_under_mouse(&window, WIDTH);
				j = get_game_piece_under_mouse(&window, HEIGHT);

				if (i != DIMENSION_SENTINEL && j != DIMENSION_SENTINEL 
					&& get_game_matrix_value(&game_state, i, j) 
					== GAME_STATE_SENTINEL)
				{
					set_game_matrix_value(&game_state, i, j, 
						get_game_player(&game_state));

					draw_window(&window, &game_state, &graphic_resources);

					if (check_victory_conditions(&game_state, 
						get_game_player(&game_state)))
					{
						// TODO: Make an appropiate victory scene.
						SDL_Delay(2000);

						set_all_game_matrix_values(&game_state, 
							get_game_player(&game_state));
						draw_window(&window, &game_state, &graphic_resources);

						SDL_Delay(2000);

						run_game = 0;
					}

					if (get_game_player(&game_state) == MOON)
						set_game_player(&game_state, STAR);
					else if (get_game_player(&game_state) == STAR)
						set_game_player(&game_state, MOON);
				}
			
			}
		}
	}	
	
	SDL_Quit();
	
	destroy_game_state(&game_state);
	destroy_graphic_resources(&graphic_resources);
	destroy_window(&window);

    return 0;
}