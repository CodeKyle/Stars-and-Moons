#include <stdlib.h>
#include <stdio.h> //remove

#include "game_state.h"

void initialize_game_state(struct GameState *game_state)
{
	game_state->matrix = NULL;
	game_state->player_turn = -1;
}

int create_game_matrix(struct GameState *game_state, size_t rows, size_t cols)
{
	game_state->matrix = malloc(sizeof(struct Matrix));
	if (game_state->matrix == NULL)
		return 1;

	game_state->matrix->rows = rows;
	game_state->matrix->cols = cols;
	game_state->matrix->values = malloc(sizeof(int) * (rows * cols));

	if (game_state->matrix->values == NULL)
		return 2;

	initialize_game_matrix(game_state);

	return 0;
}

// TODO: Avoid hardcoding the matrix value.
void initialize_game_matrix(struct GameState *game_state)
{
	set_all_matrix_values(game_state->matrix, -1);
}

struct Matrix* get_game_matrix(const struct GameState *game_state)
{
	return game_state->matrix;
}

void set_game_matrix_value(struct GameState *game_state, size_t row,
							  size_t col, int value)
{
	set_matrix_value(game_state->matrix, row, col, value);
}

int get_game_matrix_value(const struct GameState *game_state, size_t row,
						   size_t col)
{
	return get_matrix_value(game_state->matrix, row, col);
}

int check_line(const struct GameState *game_state, size_t beg_row, 
				size_t beg_col, int row_mod, int col_mod,
				size_t limit, int player_turn)
{
	int victory_progress = 0;

	for (size_t count = 0; count < limit; count++)
	{
		if (get_matrix_value(game_state->matrix,
							 beg_row + (row_mod * count),
							 beg_col + (col_mod * count)) == player_turn)
			++victory_progress;
	}

	return victory_progress;
}

int check_victory_conditions(const struct GameState *game_state,
							 int player_turn)
{
	int victory = 0;

	// Check for horizontal victory in all rows of board.
	for (size_t row_pos = 0; row_pos < BOARD_ROWS; ++row_pos)
	{
		victory = check_line(game_state, row_pos, 0, 0, 1, 
								 VICTORY_CONDITION, player_turn);

		if (victory == VICTORY_CONDITION)
			return 1;
	} 

	// Check for vertical victory in all columns of board.
	for (size_t col_pos = 0; col_pos < BOARD_COLS; ++col_pos)
	{
		victory = check_line(game_state, 0, col_pos, 1, 0, 
								 VICTORY_CONDITION, player_turn);

		if (victory == VICTORY_CONDITION)
			return 1;
	} 

	// Check for a "forward-slash" victory.
	victory = check_line(game_state, 0, 0, 1, 1, 
							 VICTORY_CONDITION, player_turn);

	if (victory == VICTORY_CONDITION)
		return 1;

	// Check for a "back-slash" victory.
	victory = check_line(game_state, 2, 0, -1, 1, 
							 VICTORY_CONDITION, player_turn);

	if (victory == VICTORY_CONDITION)
		return 1;

	// If here, victory has not been found. Return 0.
	return 0;
}

void set_game_player(struct GameState *game_state, int player_turn)
{
	game_state->player_turn = player_turn;
}

int get_game_player(const struct GameState *game_state)
{
	return game_state->player_turn;
}

void destroy_game_matrix(struct GameState *game_state)
{
	destroy_matrix(game_state->matrix);
	game_state->matrix = NULL;
}

void destroy_game_state(struct GameState *game_state)
{
	if (game_state->matrix != NULL)
		destroy_game_matrix(game_state);
}