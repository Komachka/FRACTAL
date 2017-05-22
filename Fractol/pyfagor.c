/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyfagor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 18:38:20 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/22 18:38:21 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_pyfagor_tree(t_img *img, double size_z, double x, double y)
{
	t_point *p1;
	t_point *p2;
	double	a1;

	a1 = img->a;
	p1 = (t_point*)malloc(sizeof(t_point));
	p2 = (t_point*)malloc(sizeof(t_point));
	if (size_z > img->iterations)
	{
		size_z *= 0.7;
		p1->x = x;
		p1->y = y;
		x = x + size_z * cos(a1);
		p2->x = x;
		y = y - size_z * sin(a1);
		p2->y = y;
		get_colour_point(p1, p2, size_z, img);
		make_img_line(p1, p2, img);
		a1 = img->a;
		img->a = img->a + to_radians(img->alpha);
		draw_pyfagor_tree(img, size_z, x, y);
		img->a = a1 - to_radians(img->beta);
		draw_pyfagor_tree(img, size_z, x, y);
	}
}

void	change_a(t_fractal *f_s, int dir)
{
	t_img	*img;

	img = f_s->img_struct;
	mlx_destroy_image(f_s->mlx, f_s->img_mlx);
	f_s->img_mlx = mlx_new_image(f_s->mlx, WIDTH_I, HEIGHT_I);
	create_img(img, f_s->img_mlx);
	if (dir == UP)
		img->alpha += 5;
	else if (dir == DOWN)
		img->beta += 5;
	if (img->alpha > 360)
		img->alpha = 0;
	if (img->beta > 360)
		img->beta = 0;
	draw_pyfagor_tree(img, img->size, img->move_x, img->move_y);
	img->a = M_PI / 2;
	mlx_put_image_to_window(f_s->mlx, f_s->w, f_s->img_mlx, 0, 0);
	create_string(f_s, 0);
}

void	draw_change_pyfagor_size(int direction, t_fractal *f_s)
{
	double tmp_x;
	double tmp_y;
	double a_tmp;

	if (direction == UP)
		f_s->img_struct->size += 50;
	else if (direction == DOWN)
		f_s->img_struct->size -= 10;
	tmp_x = f_s->img_struct->move_x;
	tmp_y = f_s->img_struct->move_y;
	a_tmp = f_s->img_struct->a;
	draw_pyfagor_tree(f_s->img_struct, f_s->img_struct->size,
f_s->img_struct->move_x, f_s->img_struct->move_y);
	f_s->img_struct->move_x = tmp_x;
	f_s->img_struct->move_y = tmp_y;
	f_s->img_struct->a = a_tmp;
}

void	change_iteration_pyfagor(t_fractal *f_s, int i)
{
	int		di;
	t_img	*img;
	t_img	*zero;

	di = 1;
	zero = add_valueses(PYFAGOR);
	img = f_s->img_struct;
	if (i == UP && img->iterations != 1)
		f_s->img_struct->iterations -= di;
	else if (i == DOWN)
		f_s->img_struct->iterations += di;
	mlx_destroy_image(f_s->mlx, f_s->img_mlx);
	f_s->img_mlx = mlx_new_image(f_s->mlx, WIDTH_I, HEIGHT_I);
	create_img(f_s->img_struct, f_s->img_mlx);
	draw_pyfagor_tree(img, img->size, img->move_x, img->move_y);
	img->a = zero->a;
	free(zero);
	mlx_put_image_to_window(f_s->mlx, f_s->w, f_s->img_mlx, 0, 0);
	create_string(f_s, 0);
}

void	draw_change_pyfagor_move(int direction, t_img *i_s)
{
	double tmp_x;
	double tmp_y;
	double dp;
	double a_tmp;

	dp = 10;
	if (direction == LEFT)
		i_s->move_x += dp;
	else if (direction == RIGHT)
		i_s->move_x -= dp;
	else if (direction == DOWN)
		i_s->move_y += dp;
	else if (direction == UP)
		i_s->move_y -= dp;
	tmp_x = i_s->move_x;
	tmp_y = i_s->move_y;
	a_tmp = i_s->a;
	draw_pyfagor_tree(i_s, i_s->size,
i_s->move_x, i_s->move_y);
	i_s->move_x = tmp_x;
	i_s->move_y = tmp_y;
	i_s->a = a_tmp;
}
