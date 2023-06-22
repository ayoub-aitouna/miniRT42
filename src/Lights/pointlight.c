#include "headers/pointlight.h"

light_t	*new_light(vector_t *position, vector_t *color, double intensity)
{
	light_t	*light;

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
int	calculatIlumination(light_t *this, vector_t *localNormal,
		vector_t *initPoint, double *intensity, vector_t *Color, scene_t *scene, object_t* cur_Object)
{
	vector_t *lightDir = normalized_sub(this->position, initPoint);
	double light_dist = vector_lenght(*minus(this->position, initPoint));

	t_list *tmp = scene->m_object_list;
	object_t* object = NULL;
	int ip = 0;

	while (tmp) {

		object = ((object_t*) tmp->content);
		if(object != NULL)
		{
			if(object != cur_Object)
			{
			}
		}
		tmp = tmp->next;
	}

	double angle = acos(dot(*localNormal, *lightDir));
	if (angle > HALFPI)
		return (0);
	*Color = *this->base_color;
	*intensity = (this->m_intensity * (1 - (angle / HALFPI)));
	free(lightDir);
	return (1);
}
