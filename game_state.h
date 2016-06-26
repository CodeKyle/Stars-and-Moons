#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "constants.h"
#include "matrix.h"

/*  GameState is a structure that contains information about the state of the
	game. It is intended to be use to keep track of the majority of the native
	game logic, specifically excluding any details about the library used for
	windows, input, graphics, and so forth. */
struct GameState
{
	struct Matrix *matrix;
	int player_turn;
};

/*	Initializes all variables in 'game_state'. 
	Note: Be sure to call destroy_game_matrix() to prevent memory leaks. */
void initialize_game_state(struct GameState *game_state);

/*	Initializes all values of the matrix in 'game_state.
	Note: This function is called by initialize_game_state(), so there is no
		need to call it manually. */
void initialize_game_matrix(struct GameState *game_state);

/*	Creates the matrix within 'game_state', which will then contain 'rows' rows
	and 'cols' columns. 
	Returns 0 if successful, otherwise:
		1 if the matrix could not be allocated.
		2 if the values in matrix could not be allocated.
	Note: The destroy_game_matrix() function is called by destroy_game_state(),
		so there is no need to call it manually. */
int create_game_matrix(struct GameState *game_state, size_t rows, size_t cols);

/*	TODO: Remove this function. Direct access to the matrix in 'game_state'
		should not be provided. */
struct Matrix* get_game_matrix(const struct GameState *game_state);

/*	Sets the matrix in 'game_state' to contain the value 'value' at position
	('row', 'col'). */
void set_game_matrix_value(struct GameState *game_state, size_t row,
							  size_t col, int value);

/*	Gets the value of the matrix in 'game_state' at position ('row', 'col'). */
int get_game_matrix_value(const struct GameState *game_state, size_t row,
						   size_t col);

/*	Sets the player_turn in 'game_state' to 'player_turn'. */
void set_game_player(struct GameState *game_state, int player_turn);

/*	Gets the current player_turn in 'game_state'. */
int get_game_player(const struct GameState *game_state);

/*	Frees all the matrix memory in 'game_state'.
	Note: This function is called by destroy_game_state(), so there is no need
		to call it manually. */
void destroy_game_matrix(struct GameState *game_state);

/*	Frees all the memory in 'game_state'. */
void destroy_game_state(struct GameState *game_state);

#endif