#include <stdio.h>
#include <stdbool.h>

#include "matrix.h"

int main(int argc, char *argv[])
{
	struct Matrix *matrix;
	matrix = create_matrix(3, 3);

	set_all_matrix_values(matrix, -1);
	print_all_matrix_values(matrix, true);

	int num = 0;
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			set_matrix_value(matrix, i, j, num++);
		}
	}
	print_all_matrix_values(matrix, false);
	
	destroy_matrix(matrix);
    return 0;
}

