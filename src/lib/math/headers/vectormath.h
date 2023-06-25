#ifndef MATH_H
#define MATH_H

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "types.h"
#include <stdio.h>
void print_vector(vector_t v);
float vector_lenght(vector_t v);
float vector_lenght2(vector_t v);
vector_t *normalized(vector_t *v);
float normalize(vector_t *v);
vector_t *vector(float x, float y, float z);
vector_t *copy_vector(vector_t v);
vector_t *equal(vector_t *target, vector_t *v);
vector_t *minus(vector_t *target, vector_t *v);
vector_t *addition(vector_t *target, vector_t *v);
vector_t *muliplication(vector_t *target, vector_t *v);
vector_t *num_muliplication(vector_t *target, float num);
vector_t *division(vector_t *target, vector_t *v);
vector_t *num_division(vector_t *target, float l);
float dot(vector_t v, vector_t u);
vector_t *cross(vector_t v, vector_t u);
vector_t *from_mt_to_vt(matrix_t mt);
vector_t *normalized_sub(vector_t *u, vector_t* v);


/*************************************************/
/***********   Memory Safe Funtions     **********/
/*************************************************/
void free_at_index(void *ptr1, void *ptr2, int index);
vector_t *ms_minus(vector_t *target, vector_t *v, int free_at);
vector_t *ms_addition(vector_t *target, vector_t *v, int free_at);
vector_t *ms_division(vector_t *target, vector_t *v, int free_at);
vector_t *ms_muliplication(vector_t *target, vector_t *v, int free_at);
vector_t *ms_num_muliplication(vector_t *target, float num);
double vector_distance(vector_t *u, vector_t *v);
#endif
