#include <stdio.h>
#include <stdbool.h>

#include "constants.h"
#include "game_state.h"
#include "matrix.h"

int main(int argc, char *argv[])
{
	printf("Welcome to Stars and Moons!\n");

	// Initialize game data.
	struct GameState game_state;
	initialize_game_state(&game_state);
	create_game_matrix(&game_state, BOARD_ROWS, BOARD_COLS);
	set_game_player(&game_state, 1);

	// Set the initial values of the board.
	int counter = -1;
	for (size_t i = 0; i < BOARD_ROWS; ++i)
	{
		for (size_t j = 0; j < BOARD_COLS; ++j)
		{
			set_game_matrix_value(&game_state, i, j, counter--);
		}
	}

	while (1) // Infinite game loop.
	{
		/* 	board_value - Current value at a spot on the board.
			pos 		- Unique identifier for a board spot. Valid values 
							are from -1 to -9. They are negative so that there
							is no difficulty telling the difference between
							these identifiers and the player marks, which are
							1 and 2.
			row, col 	- The array indices that pos uniquely represents. */
		int board_value, pos, row, col;

		do
		{
			do
			{
				printf("\n\n");

				// Bad. Don't do this.
				print_all_matrix_values(game_state.matrix, 1);

				// Get position on board.
				printf("Player %d choose a space:\n", 
					   get_game_player(&game_state));
				scanf("%d", &pos);
				//printf("pos = %d\n", pos);
			} while (pos < -9 || pos > -1); // Loop if invalid position.

			/*	Some tricky math to convert the pos value into a row, column
				pair. */
			pos = -pos;
			pos -= 1;
			col = (pos % BOARD_COLS);
			row = (pos / BOARD_ROWS);
			//printf("curr_row = %d, curr_col = %d\n", r, c);

			// Get the current value at those indices.
			board_value = get_game_matrix_value(&game_state, row, col);
		} while (board_value == 1 || board_value == 2); // Loop if claimed.

		// Claim the position on the board.
		set_game_matrix_value(&game_state, row, col, 
							  get_game_player(&game_state));

		// Check victory condition.

		// Switch player.
		/*
		if (get_game_player(&game_state) == 1)
			set_game_player(&game_state, 2);
		else if (get_game_player(&game_state) == 2)
			set_game_player(&game_state, 1);
		*/
	}

	// Clean up.
	destroy_game_state(&game_state);

    return 0;
}