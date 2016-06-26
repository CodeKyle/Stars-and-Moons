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



int check_path(const struct GameState *game_state, int player_turn, 
				int curr_row, int curr_col, int row_mod, int col_mod,
				int victory_condition)
{
	// Make sure index will not be out of range.
	//printf("row mod = %d, col_mod = %d\n", row_mod, col_mod);
	//printf("victory condition = %d\n", victory_condition);
	int last_row, last_col;

	if (row_mod != 0)
		last_row = curr_row + (row_mod * victory_condition) - 1;
	else 
		last_row = curr_row;

	if (col_mod != 0)
		last_col = curr_col + (col_mod * victory_condition) - 1;
	else
		last_col = curr_col;

	//printf("last_row = %d, last_col = %d\n", last_row, last_col);

	int victory_progress = 0;

	if ( (row_mod != 0) && (last_row < 0 || last_row >= BOARD_ROWS) || 
		 (col_mod != 0) && (last_col < 0 || last_col >= BOARD_COLS))
	{
		printf("check_path out of range -1\n");
		return -1;
	}
	else
	{
		for (size_t i = curr_row; i <= last_row; i += row_mod)
		{
			for (size_t j = curr_col; j <= last_col; j += col_mod)
			{
				if (get_matrix_value(game_state->matrix, i, j) == player_turn)
				{
					++victory_progress;
					//printf("victory_progress == %d\n", victory_progress);
					if (victory_progress == victory_condition)
						return 1;
				}

			}
		}
	}

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