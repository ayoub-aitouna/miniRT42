#include "../headers/types.h"
#include "headers/spher.h"

void p_int_point_propreties(vector_t *poi, object_t *this,
						  vector_t *int_point, vector_t *local_normal,
                          vector_t *local_color)
{
	vector_t *origin;
    vector_t *normal_fp;
	vector_t *global_origin;
	vector_t *m_normal;
	vector_t *int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);
	
    origin = vector(0.0, 0.0, 0.0);
    normal_fp = vector(0.0, 0.0, -1.0);

	global_origin = Apply_transform_vector(origin, FRWRD, this);
	
    m_normal = minus(Apply_transform_vector(normal_fp, FRWRD, this), global_origin);
    normalize(m_normal);

    *int_point = *int_poi;
	*local_normal = *m_normal;
	*local_color = *this->base_color;
}

/**
 *  calculat u and v;
 *  A = ray.p1;
 *  K = ray.m_lab normilazed
 *  u = Ax + tKz; & v = ay + tky; & t = kz/az;
 */
vector_t *p_calculat_int_point(ray_t *ray, vector_t k, int *status)
{
    vector_t    a;
    double      t;
    double      u;
    double      v;

    a = *ray->point1;
    *status = 1;

    if (close_enough(0.0, k.z))
        return (false(status));
    
    t = -1 * (ray->point1->z / k.z);
    
    if (t < 0.0)
        return (false(status));
    
    u = a.x + (t * k.x);
    v = a.y + (t * k.y);

    if (fabs(u) >= 1.0 || fabs(v) >= 1.0)
        return (false(status));
    else
        return (addition(ray->point1, num_muliplication(&k, t)));
}

int p_int_test(object_t *this, ray_t *camera_ray, vector_t *int_point,
                vector_t *local_normal, vector_t *local_color)
{
    vector_t *poi;
    ray_t *bck_ray;
    vector_t vhat;
    int status;

    bck_ray = Apply_transform(camera_ray, this, BCKWRD);

    vhat = *bck_ray->m_lab;
    normalize(&vhat);

    poi = p_calculat_int_point(bck_ray, vhat, &status);
    if (status == 0)
        return (FALSE);

    p_int_point_propreties(poi, this, int_point, local_normal, local_color);

    free(bck_ray);
    free(poi);
    return (TRUE);
}

object_t *plane(vector_t *translation, vector_t *rotation,
                vector_t *scal, vector_t *color)
{
    object_t *plane;
    plane = object_base(translation, rotation, scal, color);
    plane->test_inter = p_int_test;
    return (plane);
}
