#include "headers/pointlight.h"

light_t	*new_light(vector_t *position, vector_t *color, double intensity)
{
	light_t *light;

	light = malloc(sizeof(light_t));
	light->base_color = color;
	light->m_intensity = intensity;
	light->position = position;
	return (light);
}