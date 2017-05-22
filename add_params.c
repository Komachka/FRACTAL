/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:06:32 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/21 21:08:40 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractal	*create_params(int size, char *fractals)
{
	int			i;
	void		*mlx;
	int			id;
	t_fractal	*fractal_struct;

	i = 1;
	while (i < size)
	{
		id = fork();
		if (id == 0)
		{
			fractals += i;
			break ;
		}
		i++;
	}
	mlx = mlx_init();
	fractal_struct = (t_fractal*)malloc(sizeof(t_fractal));
	fractal_struct->mlx = mlx;
	create_size_for_img(fractal_struct, *fractals);
	return (fractal_struct);
}

t_img		*add_valueses(int name)
{
	t_img	*zero_struct;

	zero_struct = (t_img*)malloc(sizeof(t_img));
	if (name == PYFAGOR)
		create_zero_for_p(&zero_struct);
	else
		create_zero_p_m(&zero_struct);
	if (name == MALDEBROT)
		zero_struct->zoom = 0.45;
	return (zero_struct);
}

void		create_zero_p_m(t_img **ptr)
{
	t_img	*zero_struct;

	zero_struct = *ptr;
	zero_struct->iterations = 300;
	zero_struct->zoom = 1;
	zero_struct->move_x = 0;
	zero_struct->move_y = 0;
	zero_struct->a = 0;
	zero_struct->size = 0;
	zero_struct->c_rial = C_RIAL;
	zero_struct->c_imegian = C_IMEGIAN;
}

void		create_zero_for_p(t_img **ptr)
{
	t_img	*zero_struct;

	zero_struct = *ptr;
	zero_struct->a = M_PI / 2;
	zero_struct->size = 300;
	zero_struct->move_x = PYFAGOR_C_X;
	zero_struct->move_y = PYFAGOR_C_Y;
	zero_struct->iterations = 1;
	zero_struct->zoom = 0;
	zero_struct->alpha = 45;
	zero_struct->beta = 30;
	zero_struct->season = 1;
}

void		copy_params(t_img *zero, t_img *img)
{
	img->zoom = zero->zoom;
	img->move_x = zero->move_x;
	img->move_y = zero->move_y;
	img->iterations = zero->iterations;
	img->a = zero->a;
	img->size = zero->size;
	img->c_imegian = zero->c_imegian;
	img->c_rial = zero->c_rial;
	img->alpha = zero->alpha;
	img->beta = zero->beta;
	img->season = zero->season;
}
