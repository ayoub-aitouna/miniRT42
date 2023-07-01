#include "headers/Box.h"

int	box_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	ray_t		*bckray;
	vector_t	k;
	vector_t	*a;
	vector_t	*poi;
	double		*u_values;
	double		*v_values;
	double		*solutions;
	int			i;
	double		t;
	int			index;
	int			valide_int;
	vector_t	*normal;
	vector_t	*m_normal;
	vector_t	*int_poi;

	solutions = (double[]){MAX_V, MAX_V, MAX_V, MAX_V, MAX_V, MAX_V};
	u_values = (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	v_values = (double[]){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	i = 0;
	t = MAX_V;
	valide_int = FALSE;
	bckray = Apply_transform(camera_ray, this, BCKWRD);
	k = *bckray->m_lab;
	a = bckray->point1;
	normalize(&k);
	if (!close_enough(k.z, 0.f))
	{
		solutions[0] = (a->z - 1.0) / -k.z;
		solutions[1] = (a->z + 1.0) / -k.z;
		u_values[0] = a->x + k.x * solutions[0];
		v_values[0] = a->y + k.y * solutions[0];
		u_values[1] = a->x + k.x * solutions[1];
		v_values[1] = a->y + k.y * solutions[1];
	}
	if (!close_enough(k.x, 0.f))
	{
		solutions[2] = (a->x + 1.0) / -k.x;
		solutions[3] = (a->x - 1.0) / -k.x;
		u_values[2] = a->z + k.z * solutions[2];
		v_values[2] = a->y + k.y * solutions[2];
		u_values[3] = a->z + k.z * solutions[3];
		v_values[3] = a->y + k.y * solutions[3];
	}
	if (!close_enough(k.y, 0.f))
	{
		solutions[4] = (a->y + 1.0) / -k.y;
		solutions[5] = (a->y - 1.0) / -k.y;
		u_values[4] = a->x + k.x * solutions[4];
		v_values[4] = a->z + k.z * solutions[4];
		u_values[5] = a->x + k.x * solutions[5];
		v_values[5] = a->z + k.z * solutions[5];
	}
	while (i < 6)
	{
		if ((solutions[i] < t && solutions[i] > 0.0) && fabs(u_values[i]) <= 1
			&& fabs(v_values[i]) <= 1)
		{
			valide_int = TRUE;
			index = i;
			t = solutions[i];
		}
		i++;
	}
	if (!valide_int)
		return (FALSE);
	poi = ms_addition(bckray->point1, num_muliplication(&k, t), 1);
	switch (index)
	{
	case 0:
		normal = vector(0, 0, 1);
		break ;
	case 1:
		normal = vector(0, 0, -1);
		break ;
	case 2:
		normal = vector(-1, 0, 0);
		break ;
	case 3:
		normal = vector(1, 0, 0);
		break ;
	case 4:
		normal = vector(0, -1, 0);
		break ;
	case 5:
		normal = vector(0, 1, 0);
		break ;
	}
	int_poi = Apply_transform_vector(poi, FRWRD, this);
	m_normal = get_norm(this, normal);
	normalize(m_normal);
	prop->int_point = *int_poi;
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	return (TRUE);
}

object_t	*box(vector_t *translation, vector_t *rotation, vector_t *scal,
		vector_t *color)
{
	object_t	*box;

	box = object_base(translation, rotation, scal, color);
	box->test_inter = box_int_test;
	box->material->shininess_coefficient = 10.f;
	box->material->reflection_coefficient = .2;
	return (box);
}
