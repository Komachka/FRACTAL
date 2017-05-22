/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/21 21:40:12 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/22 20:39:35 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char **argv)
{
	char	*fractals;
	int		i;
	char	*str_res;
	char	*ptr;

	str_res = print_start(&argc);
	if (str_res == NULL)
		return (0);
	fractals = "JMP";
	ptr = str_res;
	while (argc > 0)
	{
		i = 0;
		while (fractals[i])
		{
			check_input(fractals[i], argv[argc], &str_res);
			i++;
		}
		argc--;
	}
	create_img_for_fractal(ptr);
	ft_strdel(&ptr);
}

void	check_input(char fractal, char *string_input, char **l_str_res)
{
	char	*str;
	char	*str2;
	char	*str_res;

	str_res = *l_str_res;
	str2 = ft_toupper_str(string_input);
	str = ft_strnew(1);
	str[0] = fractal;
	if (ft_strcmp(str, str2) == 0)
	{
		*str_res = fractal;
		str_res++;
	}
	ft_strdel(&str);
	*l_str_res = str_res;
}

char	*print_start(int *argc)
{
	int		tmp;
	char	*str_res;

	tmp = *argc;
	ft_putstr("Fractals:\n- Julia set		(J)\n"
"- Mandelbrot set	 (M)\n"
"- Pythagoras tree (p)\n");
	ft_putstr("Usage: ./fractol J\n       ./fractol j m p\n");
	if (tmp < 2 || tmp > 4)
	{
		ft_putstr("\nIncorect Input\n");
		return (NULL);
	}
	tmp--;
	*argc = tmp;
	str_res = ft_strnew((size_t)tmp - 1);
	ft_memset(str_res, 0, ft_strlen(str_res));
	return (str_res);
}

void	create_fractal(int c, t_img *img)
{
	t_img	*zero;

	zero = NULL;
	if (c == 'J')
		zero = add_valueses(JULIA);
	else if (c == 'M')
		zero = add_valueses(MALDEBROT);
	else if (c == 'P')
		zero = add_valueses(PYFAGOR);
	copy_params(zero, img);
	if (c == 'J')
		draw_julia(img, img->move_x, img->move_y, img->zoom);
	else if (c == 'M')
		draw_mandelbrot(img, img->move_x, img->move_y, img->zoom);
	else if (c == 'P')
	{
		draw_pyfagor_tree(img, img->size, img->move_x, img->move_y);
		img->a = zero->a;
	}
	free(zero);
}

int		exit_x(void *par)
{
	free(par);
	par = NULL;
	exit(1);
}
