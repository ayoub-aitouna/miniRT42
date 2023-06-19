#include "headers/matrix.h"
#include "headers/vectormath.h"
#include "../../headers/types.h"
#include "headers/gtfm.h"

matrix_t *Set_transform(vector_t *translation, vector_t *rotation, vector_t *scal)
{
    if (!translation || !rotation || !scal)
    {
        printf("some thing null in Set_transform \n");
        return NULL;
    }
    // define a matrix for each component of the transform
    matrix_t *translation_matrix = create_matrix(4, 4);
    printf("%p %p\n", translation_matrix, translation);
    matrix_t *rotationMatriX = create_matrix(4, 4);
    matrix_t *rotationMatriY = create_matrix(4, 4);
    matrix_t *rotationMatriZ = create_matrix(4, 4);
    matrix_t *scalMatrix = create_matrix(4, 4);

    // populate these with probpriate values
    // first translation matri

    // [1,0,0,0]
    // [0,1,0,0]
    // [0,0,1,0]
    // [0,0,0,1]
    translation_matrix->matrix[0][3] = translation->x;
    translation_matrix->matrix[1][3] = translation->y;
    translation_matrix->matrix[2][3] = translation->z;

    // [cos()	,-sin()	,0		,0]
    // [sin()	,cos()	,0		,0]
    // [0,		,0		,1		,0]
    // [0,		0,		0		,1]
    rotationMatriZ->matrix[0][0] = cos(rotation->z);
    rotationMatriZ->matrix[0][1] = -sin(rotation->z);
    rotationMatriZ->matrix[1][0] = sin(rotation->z);
    rotationMatriZ->matrix[1][1] = cos(rotation->z);

    // [cos()	,0		,sin()	,0]
    // [0		,1		,0		,0]
    // [-sin()	,0		,cos()	,0]
    // [0,		,0		,0		,1]
    rotationMatriY->matrix[0][0] = cos(rotation->y);
    rotationMatriY->matrix[0][2] = sin(rotation->y);
    rotationMatriY->matrix[2][0] = -sin(rotation->y);
    rotationMatriY->matrix[2][2] = cos(rotation->y);

    // [1		,0		,0		,0]
    // [0		,cos()	,-sin()	,0]
    // [0,		,sin()	,cos()	,0]
    // [0,		,0		,0		,1]
    rotationMatriX->matrix[1][1] = cos(rotation->x);
    rotationMatriX->matrix[1][2] = -sin(rotation->x);
    rotationMatriX->matrix[2][1] = sin(rotation->x);
    rotationMatriX->matrix[2][2] = cos(rotation->x);

    // And the scal matrex
    //  [S,0,0,0]
    //  [0,S,0,0]
    //  [0,0,S,0]
    //  [0,0,0,1]
    scalMatrix->matrix[0][0] = scal->x;
    scalMatrix->matrix[1][1] = scal->y;
    scalMatrix->matrix[2][2] = scal->z;
    // combine to give the  final transform matrix
    return mt_multiplication(mt_multiplication(mt_multiplication(translation_matrix, rotationMatriX),
                                               mt_multiplication(rotationMatriY, rotationMatriZ)),
                             scalMatrix);
}

ray_t *Apply_transform(ray_t *input_ray, object_t *this, int dirFlag)
{
    ray_t *output = malloc(sizeof(ray_t));
    output->point1 = Apply_transform_vector(input_ray->point1, dirFlag, this);
    output->point2 = Apply_transform_vector(input_ray->point2, dirFlag, this);
    output->m_lab = minus(output->point2, output->point1);
    return (output);
}

vector_t *Apply_transform_vector(vector_t *inputVector, int dirFlag, object_t *this)
{
    matrix_t *tmp = create_matrix(1, 4);
    matrix_t *resultmt = NULL;
    double values[] = {inputVector->x, inputVector->y, inputVector->z, 1.0f};
    fill_mt(tmp, values);
    if (dirFlag)
        resultmt = mt_multiplication(this->fwd_tfm, tmp);
    else
        resultmt = mt_multiplication(this->bck_tfm, tmp);
    printf("%p \n", resultmt);
    print_matrix(resultmt);
    print_matrix(this->fwd_tfm);
    print_matrix(this->bck_tfm);
    vector_t *result = vector(0, 0, 0);
    free(resultmt);
    free(tmp);
    return (result);
}
