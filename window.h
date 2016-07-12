#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

#include "game_state.h"
#include "graphic_resources.h"
#include "timer.h"

#define WINDOW_DEFAULT_WIDTH 500
#define WINDOW_DEFAULT_HEIGHT 500
#define WINDOW_DEFAULT_ASPECT_RATIO 1.333
#define GAME_BOARD_WIDTH_RATIO .7
#define GAME_BOARD_HEIGHT_RATIO .7
#define DIMENSION_SENTINEL 32767

enum DimensionType{X_POS, Y_POS, WIDTH, HEIGHT};

struct Window
{
	float x_pos, y_pos, width, height;
	char *window_title;

	SDL_Renderer* renderer;
	SDL_Window* window;

	float viewport_x_pos, viewport_y_pos, viewport_width, viewport_height;
	float viewport_aspect_ratio;

	float background_scroll_x_pos;
	float background_scroll_x_pos_mod;

	float game_piece_angle;
	float game_piece_angle_mod;
};

/*	Initializes a 'window' structure.
	Returns 0 if successful, otherwise 1. */
int initialize_window(struct Window *window); 

/*	Sets the starting position of 'window' to ('x_pos', 'y_pos'). */
void set_window_position(struct Window *window, float x_pos, float y_pos); 

/*	Sets the size of the 'window' to 'width' x 'height' pixels. */
void set_window_size(struct Window *window, float width, float height); 

/*	Sets the starting position of 'window' to ('x_pos', 'y_pos') and the size
	to 'width' x 'height' pixels. */
void set_window_dimensions(struct Window *window, float x_pos, float y_pos,
	float width, float height, float viewport_aspect_ratio); 

/*	Returns either the x-position, y-position, width, or height of 'window'
	as specified by 'dimension_type'. Valid values for 'dimension_type' are
	X_POS, Y_POS, WIDTH, AND HEIGHT. 
	Returns the value of the specified dimension, otherwise 
		DIMENSION_SENTINEL. */
int get_window_dimension(const struct Window *window, 
	enum DimensionType dimension_type); 

/*	Sets the caption of the 'window' to 'title'. */
void set_window_title(struct Window *window, char *title); 

// TODO: Add a safety check.
/*	Destroys the specified 'window'. */
int destroy_window(struct Window *window);

/*	Set the viewport 'aspect_ratio' of 'window', which determines the aspect 
	ratio of the area within the window where images are drawn. */
void set_window_viewport_aspect_ratio(struct Window *window, 
	float aspect_ratio); 

/*	Resizes the dimensions of the viewport of 'window' based on the 
	previously set aspect ratio. 
	Note: You must have called set_window_viewport_aspect_ratio() prior. */
void resize_window_viewport(struct Window *window);

/*	Draws the background on the 'window', using the images from
	'graphic_resources'. */
void draw_background(const struct Window *window,
	const struct GraphicResources *graphic_resources);

/*	Draws the gameboard on the 'window' based on information from 'game_state',
	using the images from 'graphic_resources'. */
void draw_game_board(const struct Window *window,
	const struct GraphicResources *graphic_resources);

/*	Draws the game pieces on the 'window', based on information from
	'game_state', using the images from 'graphic_resources'. */
void draw_game_pieces(const struct Window *window,
	const struct GameState *game_state,
	const struct GraphicResources *graphic_resources);

/*	Draws the all portions of 'window' based on information from 'game_state', 
	using the images from 'graphic_resources'. */
void draw_window(const struct Window *window,
	const struct GameState *game_state,
	const struct GraphicResources *graphic_resources);

/*	Processes the event loop for the 'window', based on information from
	'game_state' and using the images from 'graphic_resources'. */
int process_window_events(struct Window *window, struct GameState *game_state,
	struct GraphicResources *graphic_resources);

/*	Gets the current x-position or y-position of the mouse within 'window'
	as specified by 'dimension_type'. Valid values for 'dimension_type' are
	X_POS and Y_POS. 
	Returns the value of the specified dimension, otherwise 
		DIMENSION_SENTINEL. */
int get_mouse_position(const struct Window *window, 
	enum DimensionType dimension_type);

/*	Same function as get_mouse_position, but implemented to be more efficient.
	Currently being tested, do not use. */
int get_mouse_position_test(const struct Window *window,
	enum DimensionType dimension_type);

// TODO: Rename function and change dimension_type argument.
/*	Gets the current row index or col index of the game piece the mouse is
	over as specified by 'dimension_type'. Valid values for 'dimension_type'
	are WIDTH and HEIGHT. */
int get_game_piece_under_mouse(const struct Window *window,
	enum DimensionType dimension_type);

//	TODO: Test this.
void scroll_background(struct Window *window,
	struct GraphicResources *graphic_resources);

#endif