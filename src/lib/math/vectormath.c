#include "headers/vectormath.h"

vector_t *vector(double x, double y, double z)
{
	vector_t *vector;

	vector = malloc(sizeof(vector_t));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

vector_t *copy_vector(vector_t v)
{
	return (vector(v.x, v.y, v.z));
}

double vector_lenght2(vector_t v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double vector_lenght(vector_t v)
{
	return (sqrtf(vector_lenght2(v)));
}

vector_t *normalized(vector_t *v)
{
	vector_t *n_v;

	n_v = copy_vector(*v);
	normalize(n_v);
	return (n_v);
}

double normalize(vector_t *v)
{
	double l;

	l = vector_lenght(*v);
	v->x /= l;
	v->y /= l;
	v->z /= l;
	return (l);
}

vector_t *equal(vector_t *target, vector_t *v)
{
	vector_t *new;

	new = copy_vector(*target);
	new->x = v->x;
	new->y = v->y;
	new->z = v->z;
	return (new);
}

vector_t *minus(vector_t *target, vector_t *v)
{
	vector_t *new;

	new = copy_vector(*target);
	new->x -= v->x;
	new->y -= v->y;
	new->z -= v->z;
	return (new);
}

vector_t *addition(vector_t *target, vector_t *v)
{
	vector_t *new;

	new = copy_vector(*target);
	new->x += v->x;
	new->y += v->y;
	new->z += v->z;
	return (new);
}

vector_t *muliplication(vector_t *target, vector_t *v)
{
	vector_t *new;

	new = copy_vector(*target);
	new->x *= v->x;
	new->y *= v->y;
	new->z *= v->z;
	return (new);
}

vector_t *num_muliplication(vector_t *target, double num)
{
	vector_t *new;

	new = copy_vector(*target);
	new->x *= num;
	new->y *= num;
	new->z *= num;
	return (new);
}

vector_t *division(vector_t *target, vector_t *v)
{
	vector_t *new;

	new = copy_vector(*target);
	new->x /= v->x;
	new->y /= v->y;
	new->z /= v->z;
	return (new);
}

vector_t *num_division(vector_t *target, double num)
{
	vector_t *new;

	new = copy_vector(*target);
	new->x /= num;
	new->y /= num;
	new->z /= num;
	return (new);
}

double dot(vector_t v, vector_t u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

vector_t *cross(vector_t v, vector_t u)
{
	return (vector(v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x));
}

vector_t *from_mt_to_vt(matrix_t mt)
{
	if (mt.cols != 3 || mt.rows != 1)
		return (NULL);
	return (vector(mt.matrix[0][0], mt.matrix[0][1], mt.matrix[0][2]));
}

void print_vector(vector_t v)
{
	printf("| %f, %f, %f |\n", v.x, v.y, v.z);
}

vector_t *normalized_sub(vector_t *u, vector_t *v)
{
	vector_t *re;
	re = minus(u, v);
	normalize(re);
	return (re);
}

/*************************************************/
/***********   Memory Safe Funtions     **********/
/*************************************************/

void free_at_index(void *ptr1, void *ptr2, int index)
{
	if (index == 0 || index == 2)
		free(ptr1);
	if (index == 1 || index == 2)
		free(ptr2);
}

vector_t *ms_minus(vector_t *target, vector_t *v, int free_at)
{
	vector_t *result;
	result = minus(target, v);
	free_at_index(target, v, free_at);
	return (result);
}

vector_t *ms_addition(vector_t *target, vector_t *v, int free_at)
{
	vector_t *result;
	result = addition(target, v);
	free_at_index(target, v, free_at);
	return (result);
}

vector_t *ms_division(vector_t *target, vector_t *v, int free_at)
{
	vector_t *result;
	result = division(target, v);
	free_at_index(target, v, free_at);
	return (result);
}

vector_t *ms_muliplication(vector_t *target, vector_t *v, int free_at)
{
	vector_t *result;
	result = muliplication(target, v);
	free_at_index(target, v, free_at);
	return (result);
}

vector_t *ms_num_muliplication(vector_t *target, double num)
{
	vector_t *result;
	result = num_muliplication(target, num);
	free(target);
	return (result);
}



/*************************************************/
/***********   Advance vectors Math     **********/
/*************************************************/


/**
 * r = l - 2(l.n).n
 * r & l & n : are vectors
 */
vector_t *Reflection_vector(vector_t *l, vector_t *n)
{
	vector_t *r;
	double ln = dot(*l, *n);
	r = ms_minus(l, num_muliplication(n, 2 * ln), 1);
	normalize(r);
	return (r);
}

double vector_distance(vector_t *u, vector_t *v)
{
	vector_t *result;
	double distance = 0.0f;

	result = minus(u, v);
	distance = vector_lenght(*result);
	free(result);
	return (distance);
}