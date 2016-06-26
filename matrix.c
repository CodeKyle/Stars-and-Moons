#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

struct Matrix* create_matrix(size_t rows, size_t cols)
{
    struct Matrix *new_matrix = malloc(sizeof(struct Matrix));

    new_matrix->rows = rows;
    new_matrix->cols = cols;
    new_matrix->values = malloc(sizeof(int) * (rows * cols));

    return new_matrix;
}

void set_matrix_value(struct Matrix *matrix, size_t row, size_t col, int value)
{
    matrix->values[matrix->rows * row + col] = value;
}

void set_all_matrix_values(struct Matrix* matrix, int value)
{
    int rows = matrix->rows;
    int cols = matrix->cols;

    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            set_matrix_value(matrix, i, j, value);
}

int get_matrix_value(const struct Matrix* matrix, size_t row, size_t col)
{
    return matrix->values[matrix->rows * row + col];
}

void print_matrix_value(const struct Matrix* matrix, size_t row, size_t col)
{
    printf("%2d ", matrix->values[matrix->rows * row + col]);
}

void print_all_matrix_values(const struct Matrix* matrix, bool break_rows)
{
    int rows = matrix->rows;
    int cols = matrix->cols;

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            print_matrix_value(matrix, i, j);
        }

        if (break_rows)
            printf("\n");
    }
}

void destroy_matrix(struct Matrix* matrix)
{
    if (matrix != NULL)
    {
        if (matrix->values != NULL)
            free(matrix->values);

        free(matrix);
    }
}
