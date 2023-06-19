#ifndef TYPES_H
#define TYPES_H

#ifndef PI
#define PI 3.1415926f
#endif

#ifndef HALFPI
#define HALFPI  1.5707963f
#endif

typedef struct matrix{
	int rows;
	int cols;
	double **matrix;
} matrix_t;

typedef struct vector
{
	float x, y, z;
} vector_t;

typedef struct vector2{
	float x,y;
} vector2_t;

typedef		vector_t point_t;

#endif
