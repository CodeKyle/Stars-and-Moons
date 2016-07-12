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

	//	Initialize the window.
	struct Window window;	
	if (initialize_window(&window) != 0)
		return 2;

	set_window_title(&window, "Stars and Moons");
	set_window_dimensions(&window, 50, 50, WINDOW_DEFAULT_WIDTH,
		WINDOW_DEFAULT_HEIGHT, WINDOW_DEFAULT_ASPECT_RATIO);

	//	Initializes with room for five images.
	//	TODO: Remove the hardcoded number.
	struct GraphicResources graphic_resources;
	if (initialize_graphic_resources(&graphic_resources, 5) != 0)
		return 3;

	int image_errors = 0;
	if ((image_errors = load_all_images(5, &graphic_resources, window.renderer)) != 0)
	{
		printf("Error loading %d image(s).\n", image_errors);
		return 4;		
	}

	//	Initialize game data.
	struct GameState game_state;
	if (initialize_game_state(&game_state, BOARD_ROWS, BOARD_COLS) != 0)
		return 5;

	set_game_player(&game_state, STAR);
	set_all_game_matrix_values(&game_state, GAME_STATE_SENTINEL);

	draw_window(&window, &game_state, &graphic_resources);

	int frames_counted = 0;

	int run_game = 1;
	while (run_game == 1)
	{
		++frames_counted;
		
		run_game = process_window_events(&window, &game_state, 
			&graphic_resources);
		draw_window(&window, &game_state, &graphic_resources);

		if (run_game == 2)
		{
			set_all_game_matrix_values(&game_state, GAME_STATE_SENTINEL);
			run_game = 1;

		}
	}	

	//	Calculate an estimate of the game's FPS.
	Uint32 time_since_start = SDL_GetTicks();
	int seconds = time_since_start / 1000;
	int fps = frames_counted / seconds;
	
	printf("Rendered %d frames in %lu seconds\n",
		frames_counted, time_since_start / 1000);
	printf("FPS = %d\n", fps);
	
	//	Free all the memories.
	destroy_game_state(&game_state);
	destroy_graphic_resources(&graphic_resources);
	destroy_window(&window);

	SDL_Quit();

    return 0;
}