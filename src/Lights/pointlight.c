#include "headers/pointlight.h"

light_t *new_light(vector_t *position, vector_t *color, double intensity)
{
	light_t *light;

	light = malloc(sizeof(light_t));
	light->base_color = color;
	light->m_intensity = intensity;
	light->position = position;
	return (light);
}
/**
 * @brief I = Li * (1 - (angle / (PI/2) ))

	* @brief angle(angle btween localnormal & lightDir) = cos^-1(localNormal.lightDir)
 * @return light Intesity as double
 */
int calculatIlumination(light_t *this, vector_t *localNormal,
						vector_t *initPoint, double *intensity, vector_t *Color, scene_t *scene,
						object_t *cur_Object)
{
	vector_t *lightDir;
	double light_dist;
	t_list *tmp;
	object_t *object;
	ray_t *m_ray;
	vector_t l_ip;
	vector_t l_normal;
	vector_t l_color;
	int valide_i;
	double dist;
	double angle;

	lightDir = minus(this->position, initPoint);
	normalize(lightDir);
	light_dist = vector_distance(this->position, initPoint);
	tmp = scene->m_object_list;
	object = NULL;
	m_ray = ray(copy_vector(*initPoint), copy_vector(*this->position));
	valide_i = FALSE;
	dist = 0;
	while (tmp)
	{
		object = ((object_t *)tmp->content);
		if (object != NULL)
		{
			if (object != cur_Object)
			{
				valide_i = object->test_inter(object, m_ray, &l_ip, &l_normal,
											  &l_color);
				dist = vector_distance(&l_ip, m_ray->point1);
				if (dist > light_dist)
					valide_i = FALSE;
				if (valide_i)
				{
					free(lightDir);
					delete_ray(m_ray);
					return (FALSE);
				}
			}
		}
		tmp = tmp->next;
	}
	delete_ray(m_ray);
	angle = acos(dot(*localNormal, *lightDir));
	free(lightDir);
	if (angle > HALFPI)
		return (FALSE);
	*Color = *this->base_color;
	*intensity = (this->m_intensity * (1 - (angle / HALFPI)));
	return (TRUE);
}

void delete_light(light_t *this)
{
	if (this)
	{
		if (this->base_color)
			free(this->base_color);
		if (this->position)
			free(this->position);
		free(this);
	}
}

void delete_light_list(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		delete_light(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}