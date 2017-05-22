/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyfagor_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:40:28 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/22 18:40:30 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	get_colour_point(t_point *p1, t_point *p2, double size_z,
t_img *img)
{
	double iterations;

	iterations = img->iterations;
	if (img->season == 1)
		spring_time(p1, p2, iterations, size_z);
	else if (img->season == 2)
		summer_time(p1, p2, iterations, size_z);
	else if (img->season == 3)
		fall_time(p1, p2, iterations, size_z);
	else if (img->season == 4)
		winter_time(p1, p2, iterations, size_z);
}

void	winter_time(t_point *p1, t_point *p2, double iterations, double z)
{
	if (z / 2 > iterations)
	{
		p1->colour = SEASON41;
		p2->colour = SEASON42;
	}
	else
	{
		p1->colour = SEASON43;
		p2->colour = SEASON44;
	}
}

void	fall_time(t_point *p1, t_point *p2, double iterations, double z)
{
	if (z / 2 > iterations)
	{
		p1->colour = SEASON31;
		p2->colour = SEASON32;
	}
	else
	{
		p1->colour = SEASON33;
		p2->colour = SEASON34;
	}
}

void	summer_time(t_point *p1, t_point *p2, double iterations, double z)
{
	if (z / 2 > iterations)
	{
		p1->colour = SEASON21;
		p2->colour = SEASON22;
	}
	else
	{
		p1->colour = SEASON23;
		p2->colour = SEASON24;
	}
}

void	spring_time(t_point *p1, t_point *p2, double iterations, double z)
{
	if (z / 2 > iterations)
	{
		p1->colour = SEASON11;
		p2->colour = SEASON12;
	}
	else
	{
		p1->colour = SEASON13;
		p2->colour = SEASON14;
	}
}
