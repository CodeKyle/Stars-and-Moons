#include <stdio.h>
#include <stddef.h>

#include "constants.c"
#include "matrix.h"

void clear_matrix(int blank, int width, int height, int matrix[width][height])
{
    for (size_t r = 0; r < width; ++r)
    {
        for (size_t c = 0; c < height; ++c)
        {
            matrix[r][c] = blank;
        }
    }
}

void print_matrix_values(int width, int height, int matrix[width][height])
{
    for (size_t r = 0; r < width; ++r)
    {
        for (size_t c = 0; c < height; ++c)
        {
            printf("%2d ", matrix[r][c]);
        }
        
        printf("\n");
    }
    
    printf("\n");
}


void set_matrix_value(int value, int row, int col, int width, int height, int matrix[width][height])
{
    matrix[row][col] = value;
}

int check_matrix_value(int value, int row, int col, int width, int height, int matrix[width][height])
{
    if (matrix[row][col] == value)
        return 1;
    else  
        return 0;
}

int check_matrix_path(int value, int steps, int row, int col, int row_step, int col_step,
                      int width, int height, int matrix[width][height])
{
    // If any of the indices are out of range, return 0.
    if (row < 0 || col < 0 || row > width - 1 || col > height - 1)
        return 0;
        
    else if (steps >= 0)
    {        
        if (check_matrix_value(value, row, col, width, height, matrix))
        {
            // Branch out and check in the opposite directions for the same 'value'.
            return 1 + check_matrix_path(value, steps - 1, row - row_step, col - col_step, row_step, col_step, width, height, matrix)
                     + check_matrix_path(value, steps - 1, row + row_step, col + col_step, row_step, col_step, width, height, matrix);
        }
    }
    
    return 0;
}

int check_victory(int token, int row, int col, int width, int height, int matrix[width][height])
{
    int value = 0;
    int threshold = VICTORY_CONDITION; // Hardcoded for maximum inefficiency. 
    
    // Check for horizontal victory.
    value = check_matrix_path(token, VICTORY_CONDITION - 1, row, col, 0, 1, width, height, matrix);
    //printf("Horizontal value = %d\n", value);
    if (value > threshold)
        return 1;
    
    // Check for vertical victory.
    value = check_matrix_path(token, VICTORY_CONDITION - 1, row, col, 1, 0, width, height, matrix);
    //printf("Vertical value = %d\n", value);
    if (value >  threshold)
        return 1;

    // Check for \ victory.
    value = check_matrix_path(token, VICTORY_CONDITION - 1, row, col, 1, 1, width, height, matrix);
    //printf("\\ value = %d\n", value);
    if (value >  threshold)
        return 1;
    
    // Check for / victory.
    value = check_matrix_path(token, VICTORY_CONDITION - 1, row, col, -1, 1, width, height, matrix);
    //printf("/ value = %d\n", value);
    if (value >  threshold)
        return 1;
        
    return 0;
}