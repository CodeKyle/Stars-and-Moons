#ifndef MATRIX_H
#define MATRIX_H

/*  Replaces all the integers in 'matrix' with 'blank'. */
void clear_matrix(int blank, int width, int height, int matrix[width][height]);

/*  Prints all the characters in 'matrix'. Each row appears on a new
    line, and an extra new line is added after the the last row
    is printed. */
void print_matrix_values(int width, int height, int matrix[width][height]);

/*  Sets 'matrix[row][col]' to the 'char'. */
void set_matrix_value(int value, int row, int col, int width, int height, int matrix[width][height]);

/*  Checks if 'matrix[row][col]' is equal to 'value'. Returns 1
    if true, otherwise 0. */
int check_matrix_value(int value, int row, int col, int width, int height, int matrix[width][height]);

/*  Checks how many consecutive times 'value' appears in the 'matrix'. 'step'
    specifies how many times to look in each direction, and 'row_step' and 
    col_step' specifies the adjustment row/col adjustments to be made on
    each 'step'.
    
    TODO: Clean up this function. The value returned is unpredictable. */
int check_matrix_path(int value, int steps, int row, int col, int row_step, int col_step,
                      int width, int height, int matrix[width][height]);

/*  Checks to see if a given 'value' is present in the'matrix' the amount of times
    specified by 'victory_condition', starting at position 'matrix[row][col]'.
    
    TODO: Add 'victory_condition' as an argument.*/
int check_victory(int token, int row, int col, int width, int height, int matrix[width][height]);

#endif