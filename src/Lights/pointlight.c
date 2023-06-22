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
						 vector_t *initPoint, double *intensity,
						 vector_t *Color)
{

	//TODO: check if there is no object between the point and the light source
	vector_t *lightDir = minus(this->position, initPoint);
	normalize(lightDir);
	double angle = acos(dot(*localNormal, *lightDir));
	if (angle > HALFPI)
		return 0;
	*Color = *this->base_color;
	*intensity = (this->m_intensity * (1 - (angle / HALFPI)));
	return 1;
}