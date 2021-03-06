#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <stddef.h>

#include "constants.h"
#include "matrix.h"

#define BOARD_ROWS 3
#define BOARD_COLS 3
#define VICTORY_CONDITION 3
#define GAME_STATE_SENTINEL -1

/*  GameState is a structure that contains information about the state of the
	game. It is intended to be use to keep track of the majority of the native
	game logic, specifically excluding any details about the library used for
	windows, input, graphics, and so forth. */
struct GameState
{
	struct Matrix *matrix;
	int player_turn;
	
	int run_game;
};

/*	Initializes all variables in 'game_state'. 
	Note: Be sure to call destroy_game_matrix() to prevent memory leaks. */
int initialize_game_state(struct GameState *game_state, 
	size_t rows, size_t cols);

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

/*	Sets the matrix in 'game_state' to contain the value 'value' at position
	('row', 'col'). */
void set_game_matrix_value(struct GameState *game_state, size_t row,
	size_t col, int value);

/*	Sets all of the matrix values 'game_state' to contain the value 'value'. */
void set_all_game_matrix_values(struct GameState *game_state, int value);

/*	Gets the value of the matrix in 'game_state' at position ('row', 'col'). */
int get_game_matrix_value(const struct GameState *game_state, size_t row,
	size_t col);

/*	Checks the amount of consecutive instances of 'player_turn' in the matrix
	of 'game_state'. The first position checked is ('beg_row', 'beg_col').
	Arguments 'row_mod' and 'col_mod' determine what direction the check
	is taking place in. */	
int check_line(const struct GameState *game_state, size_t beg_row, 
	size_t beg_col, int row_mod, int col_mod, size_t limit, int player_turn);

/*	Checks all possible victory conditions.
	Returns 1 if victory condition is met. */
int check_victory_conditions(const struct GameState *game_state,
	int player_turn);

/*	Sets the player_turn in 'game_state' to 'player_turn'. */
void set_game_player(struct GameState *game_state, int player_turn);

/*	Gets the current player_turn in 'game_state'. */
int get_game_player(const struct GameState *game_state);

/*	Frees all the matrix memory in 'game_state'.
	Note: This function is called by destroy_game_state(), so there is no need
		to call it manually. */
int destroy_game_matrix(struct GameState *game_state);

/*	Frees all the memory in 'game_state'. */
int destroy_game_state(struct GameState *game_state);

#endif