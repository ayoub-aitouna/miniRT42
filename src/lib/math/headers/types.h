#ifndef TYPES_H
#define TYPES_H

#ifndef PI
#define PI 3.1415926f
#endif

#ifndef HALFPI
#define HALFPI  1.5707963f
#endif

#ifndef EPSILON
#define EPSILON 1e-21f
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


#ifndef FRWRD
#define FRWRD 1
#endif

#ifndef BCKWRD
#define BCKWRD 0
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
