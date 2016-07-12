#include <stddef.h>
#include <stdlib.h>

#include "window.h"

//TODO: Update .h comments.
int initialize_window(struct Window *window)
{
	window->x_pos = window->y_pos = window->height = window->width = 0;

	window->window_title = NULL;

	window->window = SDL_CreateWindow(window->window_title, window->x_pos, 
		window->y_pos, window->width, window->height, SDL_WINDOW_RESIZABLE);

	window->renderer = SDL_CreateRenderer(window->window, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	//	Don't hardcode.
	window->background_scroll_x_pos = 0;
	window->background_scroll_x_pos_mod = 2;
	window->game_piece_angle = 0;
	window->game_piece_angle_mod = 2;

	if (window->window == NULL)
		return 1;
	else if (window->renderer == NULL)
		return 2;

	return 0;
}

void set_window_position(struct Window *window, float x_pos, float y_pos)
{
	window->x_pos = x_pos;
	window->y_pos = y_pos;

	SDL_SetWindowPosition(window->window, x_pos, y_pos);	
}

void set_window_size(struct Window *window, float width, float height)
{
	window->width = width;
	window->height = height;
	resize_window_viewport(window);

	SDL_SetWindowSize(window->window, width, height);
}

void set_window_dimensions(struct Window *window, float x_pos, float y_pos,
	float width, float height, float viewport_aspect_ratio)
{
	set_window_viewport_aspect_ratio(window, viewport_aspect_ratio);
	
	set_window_position(window, x_pos, y_pos);
	set_window_size(window, width, height);
}

int get_window_dimension(const struct Window *window, 
	enum DimensionType dimension_type)
{
	switch (dimension_type)
	{
		case X_POS:
			return window->x_pos;
			break;
		case Y_POS:
			return window->y_pos;
			break;
		case WIDTH:
			return window->width;
			break;
		case HEIGHT:
			return window->height;
			break;
		default:
			return DIMENSION_SENTINEL;
	}
}

void set_window_title(struct Window *window, char *title)
{
	window->window_title = title;
	SDL_SetWindowTitle(window->window, title);
}

int destroy_window(struct Window *window)
{
	if (window == NULL || window->window == NULL)
		return 1;

	SDL_DestroyRenderer(window->renderer);
	SDL_DestroyWindow(window->window);
	return 0;
}

void set_window_viewport_aspect_ratio(struct Window *window, 
	float aspect_ratio)
{
	window->viewport_aspect_ratio = aspect_ratio;
}

void resize_window_viewport(struct Window *window)
{
	/*	If height of the window is smaller than what it would need to be in
		order be in compliance with the aspect_ratio of the viewport, then
		resize the width of the viewport to accomodate. */
	if ( (window->width / window->viewport_aspect_ratio) > window->height)
	{
		window->viewport_height = window->height;
		window->viewport_width = window->viewport_height 
			* window->viewport_aspect_ratio;
	}
	
	// Otherwise, set the height of the viewport to accomodate its width.
	else
	{
		window->viewport_width = window->width;
		window->viewport_height = window->viewport_width 
			/ window->viewport_aspect_ratio;		
	}

	// Center the viewport.
	window->viewport_x_pos = (window->width / 2) 
		- (window->viewport_width / 2);
	window->viewport_y_pos = (window->height / 2) 
		- (window->viewport_height / 2);
}

void draw_background(const struct Window *window,
	const struct GraphicResources *graphic_resources)
{
	SDL_Rect destination;

	// Draw the background on the entire viewport.
	destination.x = window->viewport_x_pos;
	destination.y = window->viewport_y_pos;
	destination.w = window->viewport_width;
	destination.h = window->viewport_height;

	SDL_Rect chunk;
	chunk.x = window->background_scroll_x_pos;
	chunk.y = destination.y;
	chunk.w = destination.w;
	chunk.h = destination.h;
	
	SDL_RenderCopy(window->renderer, graphic_resources->textures[0],
		&chunk, &destination);
}

void draw_game_board(const struct Window *window,
	const struct GraphicResources *graphic_resources)
{
	SDL_Rect destination;

	// Size the game board based on the viewport.
	destination.w = window->viewport_width * GAME_BOARD_WIDTH_RATIO;
	destination.h = window->viewport_height * GAME_BOARD_HEIGHT_RATIO;

	// Center the game board.
	destination.x = window->viewport_x_pos 
		+ (window->viewport_width / 2) - (destination.w / 2);
	destination.y = window->viewport_y_pos 
		+ (window->viewport_height / 2) - (destination.h / 2);

	// TODO: Don't hardcode the image.
	/*
	SDL_BlitScaled(graphic_resources->images[1], NULL,
		SDL_GetWindowSurface(window->window), &destination);	
	*/
	SDL_RenderCopy(window->renderer, graphic_resources->textures[1],
		NULL, &destination);
}

void draw_game_pieces(const struct Window *window,
	const struct GameState *game_state,
	const struct GraphicResources *graphic_resources)
{
	/*	Determine the width and height of a game piece based on the
		size of the viewport. */
	float piece_width = window->viewport_width
		* GAME_BOARD_WIDTH_RATIO / BOARD_ROWS;
	float piece_height = window->viewport_height
		* GAME_BOARD_HEIGHT_RATIO / BOARD_COLS;

	// Determine the absolute pixel position of the first game piece.
	float piece_start_x = window->viewport_x_pos 
		+ (window->viewport_width / 2) 
		- (window->viewport_width * GAME_BOARD_WIDTH_RATIO / 2);
	float piece_start_y = window->viewport_y_pos 
		+ (window->viewport_height / 2) 
		- (window->viewport_height * GAME_BOARD_HEIGHT_RATIO / 2);

	// Track the current pixel positions.
	float current_x_pos = piece_start_x;
	float current_y_pos = piece_start_y;

	// Draw all game pieces using information from the GameState structure.
	for (size_t i = 0; i < BOARD_ROWS; ++i)
	{
		for (size_t j = 0; j < BOARD_COLS; ++j) 	
		{
			SDL_Rect destination;
			destination.x = current_x_pos;
			destination.y = current_y_pos;
			destination.w = piece_width;
			destination.h = piece_height;

			// TODO: Don't hardcode the image.
			// Place an image depending on the value in the game matrix.
			if (get_game_matrix_value(game_state, i, j) != GAME_STATE_SENTINEL)
			{
				/*
				SDL_BlitScaled(graphic_resources->images
					[get_game_matrix_value(game_state, i, j)], NULL,
					SDL_GetWindowSurface(window->window), &destination);	
				*/
				SDL_RenderCopyEx(window->renderer, 
					graphic_resources->textures
					[get_game_matrix_value(game_state, i, j)], NULL,
					&destination, window->game_piece_angle, NULL, 0);

			}
				
			current_x_pos += piece_width;
			
		}
			current_x_pos = piece_start_x;
			current_y_pos += piece_height;
	}		
}

void draw_window(const struct Window *window,
	const struct GameState *game_state,
	const struct GraphicResources *graphic_resources)
{
	SDL_RenderClear(window->renderer);

	draw_background(window, graphic_resources);
	draw_game_board(window, graphic_resources);
	draw_game_pieces(window, game_state, graphic_resources);

	// Check to see if the mouse is over a game piece.

	/*
	int i = DIMENSION_SENTINEL, j = DIMENSION_SENTINEL;
	i = get_game_piece_under_mouse(window, WIDTH);
	j = get_game_piece_under_mouse(window, HEIGHT);

	if (i != DIMENSION_SENTINEL && i >= 0 && j != DIMENSION_SENTINEL && j >= 0 
		&& (get_game_matrix_value(game_state, i, j) == GAME_STATE_SENTINEL))
	{
		// TODO: Draw the hover icon.
		//printf("i = %d j = %d\n", i, j);
	} */

	//SDL_UpdateWindowSurface(window->window);
	SDL_RenderPresent(window->renderer);
}

int process_window_events(struct Window *window, struct GameState *game_state,
	struct GraphicResources *graphic_resources)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			//game_state->run_game = 0;

			return 0;
		}

		else if (event.type == SDL_WINDOWEVENT)
		{
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				int window_width, window_height;

				SDL_GetWindowSize(window->window, 
					&window_width, &window_height);

				set_window_size(window, window_width, window_height);
			}

			//draw_window(window, game_state, graphic_resources);

		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			//draw_window(window, game_state, graphic_resources);
		}
	
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			/*	Check if the mouse is over a game piece and if it is 
				available. If so, claim it and check for a victory. */
			int i = DIMENSION_SENTINEL, j = DIMENSION_SENTINEL;

			// Bottleneck?
			i = get_game_piece_under_mouse(window, WIDTH);
			j = get_game_piece_under_mouse(window, HEIGHT);
			//i = get_mouse_position_test(&window, WIDTH);
			//j = get_mouse_position_test(&window, HEIGHT);
			//printf("(%d, %d)\n", i, j);

			if (i != DIMENSION_SENTINEL && j != DIMENSION_SENTINEL 
				&& get_game_matrix_value(game_state, i, j) 
				== GAME_STATE_SENTINEL)
			{
				set_game_matrix_value(game_state, i, j, 
					get_game_player(game_state));

				if (check_victory_conditions(game_state, 
					get_game_player(game_state)))
				{
					// TODO: Make an appropiate victory scene.
					set_all_game_matrix_values(game_state, 
						get_game_player(game_state));

					// Otherwise they would not see the victory.
					draw_window(window, game_state, graphic_resources);

					SDL_Delay(2000);

					game_state->run_game = 2;
					return 2;
				}

				if (get_game_player(game_state) == MOON)
					set_game_player(game_state, STAR);
				else if (get_game_player(game_state) == STAR)
					set_game_player(game_state, MOON);
			}
		
		}
	}

	window->game_piece_angle += window->game_piece_angle_mod;
	scroll_background(window, graphic_resources);
	//draw_window(window, game_state, graphic_resources);

	return 1;
}

int get_mouse_position(const struct Window *window, 
	enum DimensionType dimension_type)
{
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	if (dimension_type == X_POS)
		return mouse_x;
	else if (dimension_type == Y_POS)
		return mouse_y;
	else
		return DIMENSION_SENTINEL;
}

int get_game_piece_under_mouse(const struct Window *window,
	enum DimensionType dimension_type)
{
	/*	Determine the width and height of a game piece based on the
		size of the viewport. */

	float piece_width = window->viewport_width
		* GAME_BOARD_WIDTH_RATIO / BOARD_ROWS;
	float piece_height = window->viewport_height
		* GAME_BOARD_HEIGHT_RATIO / BOARD_COLS;

	// Determine the absolute pixel position of the first game piece.
	float piece_start_x = window->viewport_x_pos 
		+ (window->viewport_width / 2) 
		- (window->viewport_width * GAME_BOARD_WIDTH_RATIO / 2);
	float piece_start_y = window->viewport_y_pos 
		+ (window->viewport_height / 2) 
		- (window->viewport_height * GAME_BOARD_HEIGHT_RATIO / 2);

	float current_x_pos = piece_start_x;
	float current_y_pos = piece_start_y;

	int x, y;
	x = get_mouse_position(window, X_POS);
	y = get_mouse_position(window, Y_POS);

	// If mouse position is out of range, stop now.
	if (x < piece_start_x || y < piece_start_y
		|| x > piece_start_x + window->viewport_width 
			* GAME_BOARD_WIDTH_RATIO
		|| y > piece_start_y + window->viewport_height 
			* GAME_BOARD_HEIGHT_RATIO)
		return DIMENSION_SENTINEL;	

	/*	If mouse position is within range of the game board dimensions, 
		determine which [row, column] pair it would be over within
		the game matrix. */ 
	else
	{
		for (size_t i = 0; i < BOARD_ROWS; ++i)
		{
			for (size_t j = 0; j < BOARD_COLS; ++j) 	
			{
				if (x >= current_x_pos && x <= current_x_pos + piece_width 
					&& y >= current_y_pos && y <= current_y_pos + piece_height)
				{	
					if (dimension_type == WIDTH)
						return i;
					else if (dimension_type == HEIGHT)
						return j;
					else
						return DIMENSION_SENTINEL;
				}			

				current_x_pos += piece_width;
			}
				
			current_x_pos = piece_start_x;
			current_y_pos += piece_height;
		}
	}

	return DIMENSION_SENTINEL;
}

int get_mouse_position_test(const struct Window *window,
	enum DimensionType dimension_type)
{
	//Get mouse position
	int x = DIMENSION_SENTINEL, y = DIMENSION_SENTINEL;
	x = get_mouse_position(window, X_POS);
	y = get_mouse_position(window, Y_POS);

	float piece_start_x = window->viewport_x_pos 
		+ (window->viewport_width / 2) 
		- (window->viewport_width * GAME_BOARD_WIDTH_RATIO / 2);
	float piece_start_y = window->viewport_y_pos 
		+ (window->viewport_height / 2) 
		- (window->viewport_height * GAME_BOARD_HEIGHT_RATIO / 2);

	float piece_width = window->viewport_width 
		* GAME_BOARD_WIDTH_RATIO / BOARD_ROWS;
	float piece_height = window->viewport_height
		* GAME_BOARD_HEIGHT_RATIO / BOARD_COLS;

	float board_width = window->viewport_width 
		* GAME_BOARD_WIDTH_RATIO;
	float board_height = window->viewport_height 
		* GAME_BOARD_HEIGHT_RATIO;

	int relative_x = x - piece_start_x;
	int relative_y = y - piece_start_y;

	int row = relative_x / piece_width;
	int col = relative_y / piece_height;

	if (dimension_type == WIDTH)
		return col;
	else if (dimension_type == HEIGHT)
		return row;
	else
		return DIMENSION_SENTINEL;	
}


void scroll_background(struct Window *window,
	struct GraphicResources *graphic_resources)
{
	int image_width = 0;
	int image_height = 0;
	SDL_QueryTexture(graphic_resources->textures[0],
		SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STATIC,
		&image_width, &image_height);

	/*	If the end of the image is not yet visible in the window, scroll
		normally. Otherwise, if the end of the image is coming, snap back
		to the an earlier position of the image to create a seamless
		scrolling experience. */
	if (window->background_scroll_x_pos + window->viewport_width < image_width)
		window->background_scroll_x_pos += window->background_scroll_x_pos_mod;
	else
		window->background_scroll_x_pos = 
			(window->background_scroll_x_pos - window->viewport_width) / 2;
}