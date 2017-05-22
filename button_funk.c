/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_funk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:17:27 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/21 21:17:28 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	scale(t_fractal *f_s, int dir)
{
	int		n_f;
	char	c;

	mlx_destroy_image(f_s->mlx, f_s->img_mlx);
	f_s->img_mlx = mlx_new_image(f_s->mlx,
											WIDTH_I, HEIGHT_I);
	create_img(f_s->img_struct, f_s->img_mlx);
	c = f_s->c;
	n_f = what_fractal_is_it(c);
	if (n_f == JULIA || n_f == MALDEBROT)
		change_julia_mandelbrot_scale(dir, f_s->img_struct, n_f);
	else if (n_f == PYFAGOR)
		draw_change_pyfagor_size(dir, f_s);
	mlx_put_image_to_window(f_s->mlx, f_s->w, f_s->img_mlx, 0, 0);
	create_string(f_s, 0);
}

void	change_julia_mandelbrot_scale(int direction, t_img *img, int n_f)
{
	double	d_zoom;

	if (direction == DOWN)
		d_zoom = 1.1;
	else if (direction == UP)
		d_zoom = 0.9;
	img->zoom *= d_zoom;
	if (n_f == JULIA)
		draw_julia(img, img->move_x, img->move_y, d_zoom);
	else if (n_f == MALDEBROT)
		draw_mandelbrot(img, img->move_x, img->move_y, d_zoom);
}

int		mouse_move(int x, int y, t_fractal *fractal_stuct)
{
	if (fractal_stuct->flag_on == 1 && fractal_stuct->c == 'J')
		draw_julia_with_dif_set(fractal_stuct, x, y);
	return (0);
}

int		button_funk(int button, int x, int y, t_fractal *fractal_struct)
{
	if (fractal_struct->c == 'P')
	{
		fractal_struct->img_struct->move_x = x;
		fractal_struct->img_struct->move_y = y + y / 2;
		if (button == 1)
			change_iteration_pyfagor(fractal_struct, UP);
		else if (button == 2)
			change_iteration_pyfagor(fractal_struct, DOWN);
	}
	if (button == 4)
		scale(fractal_struct, UP);
	else if (button == 5)
		scale(fractal_struct, DOWN);
	return (0);
}
