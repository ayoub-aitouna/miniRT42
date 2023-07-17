/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spher.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:30 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 22:15:45 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/spher.h"

t_object	*create_sphere(t_vector *translation, t_vector *rotation,
		t_vector *scal, t_vector *color)
{
	t_object	*shphere;

	shphere = object_base(translation, rotation, scal, color);
	shphere->test_inter = sh_int_test;
	return (shphere);
}

int	sh_int_test(t_object *this, t_ray *camera_ray, t_propretries *prop)
{
	t_vector	*poi;
	t_ray		*bck_ray;
	t_vector	vhat;
	int			status;

	bck_ray = apply_transform(camera_ray, this, BCKWRD);
	vhat = *bck_ray->m_lab;
	normalize(&vhat);
	poi = calculat_int_point(bck_ray, vhat, &status);
	delete_ray(bck_ray);
	if (!status)
	{
		free(poi);
		return (FALSE);
	}
	int_point_propreties(poi, this, prop);
	free(poi);
	return (TRUE);
}

void	int_point_propreties(t_vector *poi, t_object *this, t_propretries *prop)
{
	t_vector	*m_normal;
	t_vector	*int_poi;

	int_poi = apply_transform_vector(poi, FRWRD, this);
	calculat_uv(prop, poi);
	m_normal = get_norm(this, poi);
	if (this->textures)
		m_normal = apply_bump_map_textures(this->textures, m_normal,
				prop->uv_cords);
	normalize(m_normal);
	prop->int_point = *int_poi;
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	free_list((void *[]){int_poi, m_normal}, 2);
}
