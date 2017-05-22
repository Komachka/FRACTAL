/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:30:23 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/21 21:30:24 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_julia(t_img *img, double move_dx, double move_dy, double d_zoom)
{
	t_point *p;
	int		x;
	int		y;
	int		i;

	y = 0;
	p = (t_point*)malloc(sizeof(t_point));
	img->move_x = move_dx / d_zoom;
	img->move_y = move_dy / d_zoom;
	while (y < HEIGHT_I)
	{
		x = 0;
		while (x < WIDTH_I)
		{
			i = count_iteration_julia(img, y, x, 1);
			p->colour = get_colour(i % 256, 255, 255 * (i < img->iterations));
			p->x = x;
			p->y = y;
			put_pixel_to_image(p, img);
			x++;
		}
		y++;
	}
	free(p);
}

int		count_iteration_julia(t_img *img, int y, int x, int i)
{
	static double n_r;
	static double n_i;
	static double o_r;
	static double o_i;

	n_r = (x - WIDTH_I / 2) / (0.5 * img->zoom * WIDTH_I) + img->move_x;
	n_i = (y - HEIGHT_I / 2) / (0.5 * img->zoom * HEIGHT_I) + img->move_y;
	while (i < img->iterations)
	{
		o_r = n_r;
		o_i = n_i;
		n_r = o_r * o_r - o_i * o_i + img->c_rial;
		n_i = 2 * o_r * o_i + img->c_imegian;
		if ((n_r * n_r + n_i * n_i) > 4)
			break ;
		i++;
	}
	return (i);
}

void	draw_julia_with_dif_set(t_fractal *f_s, int x, int y)
{
	double	c_rial;
	double	c_imegian;
	t_img	*img;

	img = f_s->img_struct;
	c_rial = (x - WIDTH_I / 2) / (0.5 * f_s->img_struct->zoom * WIDTH_I);
	c_imegian = (y - HEIGHT_I / 2) / (0.5 * f_s->img_struct->zoom * HEIGHT_I);
	img->move_x = 0;
	img->move_y = 0;
	f_s->img_struct->c_rial = c_rial;
	f_s->img_struct->c_imegian = c_imegian;
	mlx_destroy_image(f_s->mlx, f_s->img_mlx);
	f_s->img_mlx = mlx_new_image(f_s->mlx, WIDTH_I, HEIGHT_I);
	create_img(f_s->img_struct, f_s->img_mlx);
	draw_julia(img, img->move_x, img->move_y, img->zoom);
	mlx_put_image_to_window(f_s->mlx, f_s->w, f_s->img_mlx, 0, 0);
	create_string(f_s, 0);
}
