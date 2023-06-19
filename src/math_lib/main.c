#include "headers/matrix.h"
#include "headers/vectormath.h"
#include <stdio.h>

void printv(vector_t vector)
{
	printf("{.x %f, .y %f, .z %f}\n", vector.x, vector.y, vector.z);
}

int main(int ac, char **av)
{
	matrix_t *mt1;
	mt1 = create_matrix(4, 4);
	matrix_t *mt4 = create_matrix(4, 4);
	double values1[] = {
		8, -5, 9, 2,
		7, 5, 6, 1,
		-6, 0, 9, 6,
		-3, 0, -9, -4};

	double fbf[] = {9, 3, 0, 9,
					-5, -2, -6, -3,
					-4, 9, 6, 4,
					-7, 6, 6, 2};
	fill_mt(mt1, values1);
	fill_mt(mt4, fbf);

	printf("\nMatrix Mt1 :\n");
	print_matrix(mt1);
	printf("\nit's Invers is :\n");
	print_matrix(inverse(mt1));

	printf("\nnMatrix Mt4 :\n");
	print_matrix(mt4);
	printf("\nit's Invers is :\n");
	print_matrix(inverse(mt4));
}
