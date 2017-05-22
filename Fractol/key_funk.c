/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_funk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:33:41 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/21 21:33:42 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		my_key_funk(int keykode, t_fractal *f_s)
{
	if (keykode == 126)
		move(f_s, UP);
	if (keykode == 125)
		move(f_s, DOWN);
	if (keykode == 124)
		move(f_s, LEFT);
	if (keykode == 123)
		move(f_s, RIGHT);
	if (keykode == 49 && f_s->flag_on == 1 && f_s->c == 'J')
	{
		f_s->flag_on = 0;
		return (0);
	}
	if (keykode == 49 && f_s->flag_on == 0 && f_s->c == 'J')
	{
		f_s->flag_on = 1;
		return (0);
	}
	second_part(keykode, f_s);
	return (0);
}

void	second_part(int keykode, t_fractal *fractal_struct)
{
	if (keykode == 69 && fractal_struct->c == 'P')
		change_a(fractal_struct, UP);
	if (keykode == 78 && fractal_struct->c == 'P')
		change_a(fractal_struct, DOWN);
	if (keykode == 18)
		fractal_struct->img_struct->season = 1;
	if (keykode == 19)
		fractal_struct->img_struct->season = 2;
	if (keykode == 20)
		fractal_struct->img_struct->season = 3;
	if (keykode == 21)
		fractal_struct->img_struct->season = 4;
}

void	move(t_fractal *f_s, int direction)
{
	t_img	*img_struct;
	int		n_f;
	char	c;

	img_struct = f_s->img_struct;
	mlx_destroy_image(f_s->mlx, f_s->img_mlx);
	f_s->img_mlx = mlx_new_image(f_s->mlx, WIDTH_I, HEIGHT_I);
	create_img(img_struct, f_s->img_mlx);
	c = f_s->c;
	n_f = what_fractal_is_it(c);
	if (n_f == JULIA || n_f == MALDEBROT)
		change_moving_julia_mandelbrot_move(direction, img_struct, n_f);
	else if (n_f == PYFAGOR)
		draw_change_pyfagor_move(direction, img_struct);
	mlx_put_image_to_window(f_s->mlx, f_s->w, f_s->img_mlx, 0, 0);
	create_string(f_s, 0);
}
