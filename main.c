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

	// Initialize the window.
	struct Window window;	
	if (initialize_window(&window) != 0)
		return 2;

	set_window_title(&window, "Stars and Moons");
	set_window_dimensions(&window, 50, 50, WINDOW_DEFAULT_WIDTH,
		WINDOW_DEFAULT_HEIGHT, WINDOW_DEFAULT_ASPECT_RATIO);

	struct GraphicResources graphic_resources;

	// Provide room for five images.
	if (initialize_graphic_resources(&graphic_resources, 5) != 0)
		return 3;

	load_all_images(5, &graphic_resources);

	// Initialize game data.
	struct GameState game_state;
	if (initialize_game_state(&game_state, BOARD_ROWS, BOARD_COLS) != 0)
		return 4;

	set_game_player(&game_state, STAR);
	set_all_game_matrix_values(&game_state, GAME_STATE_SENTINEL);

	draw_window(&window, &game_state, &graphic_resources);

	SDL_Event event;
	int run_game = 1;
	
	while (run_game == 1)
	{
		process_window_events(&window, &game_state, &graphic_resources);
		if (game_state.run_game == 0)
			run_game = 0;
	}	
	
	SDL_Quit();
	
	destroy_game_state(&game_state);
	destroy_graphic_resources(&graphic_resources);
	destroy_window(&window);

    return 0;
}