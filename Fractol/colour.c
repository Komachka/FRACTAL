/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:21:04 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/21 21:21:05 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	**create_gradient(int **rgb, double dx)
{
	double	**matrix_colour;

	matrix_colour = (double **)malloc(sizeof(double*) * 3);
	matrix_colour[0] = (double*)malloc(sizeof(double) * 3);
	matrix_colour[1] = (double*)malloc(sizeof(double) * 3);
	matrix_colour[2] = (double*)malloc(sizeof(double) * 3);
	matrix_colour[0][0] = (rgb[1][0] - rgb[0][0]) / dx;
	matrix_colour[0][1] = (rgb[1][1] - rgb[0][1]) / dx;
	matrix_colour[0][2] = (rgb[1][2] - rgb[0][2]) / dx;
	matrix_colour[1][0] = rgb[0][0];
	matrix_colour[1][1] = rgb[0][1];
	matrix_colour[1][2] = rgb[0][2];
	matrix_colour[2][0] = rgb[1][0];
	matrix_colour[2][1] = rgb[1][1];
	matrix_colour[2][2] = rgb[1][2];
	return (matrix_colour);
}

void	del_delta(double **matrix_colour, t_point *point)
{
	matrix_colour[2][0] -= matrix_colour[0][0];
	matrix_colour[2][1] -= matrix_colour[0][1];
	matrix_colour[2][2] -= matrix_colour[0][2];
	point->colour = (int)matrix_colour[2][0] +
			((int)matrix_colour[2][1] << 8) + ((int)matrix_colour[2][2] << 16);
}

void	add_delta(double **matrix_colour, t_point *point)
{
	matrix_colour[1][0] += matrix_colour[0][0];
	matrix_colour[1][1] += matrix_colour[0][1];
	matrix_colour[1][2] += matrix_colour[0][2];
	point->colour = (int)matrix_colour[1][0] +
			((int)matrix_colour[1][1] << 8) + ((int)matrix_colour[1][2] << 16);
}

int		*c_rgb(int colour)
{
	int	*rgb;

	if ((rgb = (int*)malloc(sizeof(int) * 3)) == NULL)
		return (NULL);
	rgb[0] = colour & 0xFF;
	rgb[1] = colour >> 8 & 0xFF;
	rgb[2] = colour >> 16 & 0xFF;
	return (rgb);
}

int		get_colour(double h, double s, double v)
{
	t_rgb	rgb;
	t_koef	koef;

	(h == 360) ? (h = 0.) : (h /= 60.);
	koef.fract = h - ceil(h);
	koef.p = v * (1. - s);
	koef.q = v * (1. - s * koef.fract);
	koef.t = v * (1. - s * (1. - koef.fract));
	if (0. <= h && h < 1.)
		rgb = (t_rgb){.r = v, .g = koef.t, .b = koef.p};
	else if (1. <= h && h < 2.)
		rgb = (t_rgb){.r = koef.q, .g = v, .b = koef.p};
	else if (2. <= h && h < 3.)
		rgb = (t_rgb){.r = koef.p, .g = v, .b = koef.t};
	else if (3. <= h && h < 4.)
		rgb = (t_rgb){.r = koef.p, .g = koef.q, .b = v};
	else if (4. <= h && h < 5.)
		rgb = (t_rgb){.r = koef.t, .g = koef.p, .b = v};
	else if (5. <= h && h < 6.)
		rgb = (t_rgb){.r = v, .g = koef.p, .b = koef.q};
	else
		rgb = (t_rgb){.r = 0., .g = 0., .b = 0.};
	return ((int)rgb.r +
			((int)rgb.g << 8) + ((int)rgb.b << 16));
}
