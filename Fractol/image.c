/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:25:10 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/22 19:55:21 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	create_img_for_fractal(char *fractals)
{
	int			size_f;
	t_fractal	*f_s;
	char		c;

	size_f = (int)ft_strlen(fractals);
	if ((f_s = create_params(size_f, fractals)) == NULL)
		return ;
	create_img(f_s->img_struct, f_s->img_mlx);
	c = f_s->c;
	f_s->flag_on = 0;
	create_fractal(c, f_s->img_struct);
	mlx_put_image_to_window(f_s->mlx, f_s->w, f_s->img_mlx, 0, 0);
	mlx_hook(f_s->w, 17, 1L << 17, exit_x, f_s);
	mlx_hook(f_s->w, 2, 1L << 1, my_key_funk, f_s);
	mlx_hook(f_s->w, 6, 0, mouse_move, f_s);
	mlx_mouse_hook(f_s->w, button_funk, f_s);
	create_string(f_s, 0);
	mlx_loop(f_s->mlx);
}

void	create_img(t_img *img_struct, void *img_mlx)
{
	int		bit_per_pixel;
	int		size_line;
	int		endian;

	img_struct->map = mlx_get_data_addr(img_mlx, &bit_per_pixel,
										&size_line, &endian);
	img_struct->size_line = size_line;
}

void	create_size_for_img(t_fractal *f_s, char f)
{
	void	*img1;
	t_img	*img_struct1;
	char	*str;
	char	c;

	c = f;
	if (c == 'J')
		str = "Julia set";
	else if (c == 'M')
		str = "Mandelbrot set";
	else if (c == 'P')
		str = "Pythagoras tree";
	else
	{
		write(1, "Something go wrog\n", 17);
		exit(0);
	}
	img_struct1 = (t_img*)malloc(sizeof(t_img));
	img1 = mlx_new_image(f_s->mlx, WIDTH_I, HEIGHT_I);
	f_s->img_mlx = img1;
	f_s->img_struct = img_struct1;
	f_s->w = mlx_new_window(f_s->mlx, WIDTH_W, HEIGHT_W, str);
	f_s->c = c;
	f_s->string = ft_strjoin(ft_strnew(0), str);
}
