/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maldebrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:43:38 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/21 21:43:40 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_mandelbrot(t_img *img, double move_x, double move_y, double zoom)
{
	int	y;

	y = 0;
	img->move_x = move_x / zoom;
	img->move_y = move_y / zoom;
	while (y < HEIGHT_I)
	{
		x_loop_maldebrot(img, 0, y, 1);
		y++;
	}
}

void	x_loop_maldebrot(t_img *img, int x, int y, int i)
{
	double	pr;
	double	pi;
	t_point *p;

	p = (t_point*)malloc(sizeof(t_point));
	while (x < WIDTH_I)
	{
		pr = (x - WIDTH_I / 2) / (0.5 * img->zoom * WIDTH_I) + img->move_x;
		pi = (y - HEIGHT_I / 2) / (0.5 * img->zoom * HEIGHT_I) + img->move_y;
		i = count_iteration_mandelbrot(img, pi, pr, 1);
		p->colour = get_colour(i % 256, 255, 255 * (i < img->iterations));
		p->x = x;
		p->y = y;
		put_pixel_to_image(p, img);
		x++;
	}
	free(p);
}

int		count_iteration_mandelbrot(t_img *img, double pi, double pr, int i)
{
	double	n_r;
	double	n_i;
	double	o_r;
	double	o_i;

	n_i = 0;
	n_r = 0;
	while (i < img->iterations)
	{
		o_r = n_r;
		o_i = n_i;
		n_r = o_r * o_r - o_i * o_i + pr;
		n_i = 2 * o_r * o_i + pi;
		if ((n_r * n_r + n_i * n_i) > 4)
			break ;
		i++;
	}
	return (i);
}

void	change_moving_julia_mandelbrot_move(int direction, t_img *is, int n_f)
{
	double tmp_x;
	double tmp_y;

	if (direction == LEFT)
		is->move_x = (is->move_x - 0.10);
	else if (direction == RIGHT)
		is->move_x = (is->move_x + 0.10);
	else if (direction == DOWN)
		is->move_y = (is->move_y - 0.10);
	else if (direction == UP)
		is->move_y = (is->move_y + 0.10);
	tmp_x = is->move_x;
	tmp_y = is->move_y;
	if (n_f == JULIA)
		draw_julia(is, is->move_x, is->move_y, is->zoom);
	else if (n_f == MALDEBROT)
		draw_mandelbrot(is, is->move_x * is->zoom,
is->move_y * is->zoom, is->zoom);
	is->move_x = tmp_x;
	is->move_y = tmp_y;
}
