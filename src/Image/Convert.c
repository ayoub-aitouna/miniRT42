/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:56:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/17 19:56:27 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/image.h"

int	convert(double red, double green, double blue, double max)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				value;

	r = (red / max) * 255;
	g = (green / max) * 255;
	b = (blue / max) * 255;
	value = (r << 16) + (g << 8) + b;
	return (value);
}

double	max_in_channel(double **channel)
{
	int		x;
	int		y;
	double	max;
	double	value;

	value = 0;
	max = 0;
	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			value = channel[y][x];
			if (value > max)
				max = value;
			y++;
		}
		x++;
	}
	return (max);
}

double	max_color_value(t_image *image)
{
	double	m_overall_max;
	double	value;

	m_overall_max = max_in_channel(image->red);
	value = max_in_channel(image->green);
	if (value > m_overall_max)
		m_overall_max = value;
	value = max_in_channel(image->blue);
	if (value > m_overall_max)
		m_overall_max = value;
	return (m_overall_max);
}
