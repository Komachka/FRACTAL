/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_funk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 19:05:42 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/22 19:05:43 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create_string(t_fractal *f_s, double size1)
{
	char	*x;
	char	*y;
	char	*size;
	double	x1;
	double	y1;

	x1 = f_s->img_struct->move_x;
	y1 = f_s->img_struct->move_y;
	if (f_s->c == 'P')
		size1 = pifagor_string(f_s);
	else
		size1 = f_s->img_struct->zoom * 1000;
	if (f_s->c == 'J' || f_s->c == 'M')
	{
		x1 *= 100;
		y1 *= 100;
	}
	mlx_string_put(f_s->mlx, f_s->w, 10, 10, 0xFFFFFF, f_s->string);
	x = ft_strjoin("x = ", ft_itoa((int)x1));
	mlx_string_put(f_s->mlx, f_s->w, 10, 30, 0xFFFFFF, x);
	y = ft_strjoin("y = ", ft_itoa((int)y1));
	mlx_string_put(f_s->mlx, f_s->w, 10, 50, 0xFFFFFF, y);
	size = ft_strjoin("size = ", ft_itoa((int)size1));
	mlx_string_put(f_s->mlx, f_s->w, 10, 70, 0xFFFFFF, size);
}

double	pifagor_string(t_fractal *f_s)
{
	double size;
	double alpha;
	double beta;

	size = f_s->img_struct->size;
	alpha = f_s->img_struct->alpha;
	beta = f_s->img_struct->beta;
	mlx_string_put(f_s->mlx, f_s->w, 10, 90, 0xFFFFFF,
	ft_strjoin("alpha = ", ft_itoa((int)alpha)));
	mlx_string_put(f_s->mlx, f_s->w, 10, 110, 0xFFFFFF,
	ft_strjoin("beta = ", ft_itoa((int)beta)));
	return (size);
}
