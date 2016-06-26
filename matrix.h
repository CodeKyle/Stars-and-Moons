#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

/*  Matrix is a structure that represents a grid with a specified amount of
    'rows' and 'cols', each position containing its own integer value. */
struct Matrix
{
    size_t rows;
    size_t cols;
    int *values;
};

/*  Creates a new matrix with 'rows' rows and 'cols' columns.
    Returns a pointer to the created matrix.
    Note: Be sure to call destroy_matrix() to prevent memory leaks. */
struct Matrix* create_matrix(size_t rows, size_t cols);

/*  Sets the 'value' at position ('row', 'col') in 'matrix'. */
void set_matrix_value(struct Matrix* matrix, size_t row, size_t col, 
                        int value);

/*  Sets the 'value' for all positions in 'matrix'. */
void set_all_matrix_values(struct Matrix* matrix, int value);

/*  Gets the value held at position ('row', 'col') of 'matrix'. 
    Returns the value at said position. */
int get_matrix_value(struct Matrix* matrix, size_t row, size_t col);

/*  Prints the 'value' at position ('row', 'col') in 'matrix'. */
void print_matrix_value(const struct Matrix* matrix, size_t row, size_t col);

/*  Prints every 'value' in 'matrix'. If 'row_break' is true, then a new line
    will be printed after each row. */
void print_all_matrix_values(const struct Matrix* matrix, bool break_rows);

/*  Destroys the 'matrix', freeing all memory allocated within the structure.
    Note: All pointers related to the structure will be set to NULL after. */
void destroy_matrix(struct Matrix* matrix);

#endif