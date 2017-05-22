/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kstorozh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 20:27:58 by kstorozh          #+#    #+#             */
/*   Updated: 2017/05/22 20:27:59 by kstorozh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

# define WIDTH_W 1000
# define HEIGHT_W 1000

# define WIDTH_I WIDTH_W
# define HEIGHT_I HEIGHT_W
# define UP 1
# define DOWN -1
# define LEFT -2
# define RIGHT 2
# define C_RIAL -0.7
# define C_IMEGIAN 0.27015
# define JULIA 1
# define MALDEBROT 2
# define PYFAGOR 3
# define PYFAGOR_C_X WIDTH_W / 2
# define PYFAGOR_C_Y HEIGHT_W * 0.75
# define SEASON11 0xA1856E
# define SEASON12 0x7A5230
# define SEASON13 0x3F553F
# define SEASON14 0x4ca64c
# define SEASON21 0xA1856E
# define SEASON22 0x7A5230
# define SEASON24 0xff0000
# define SEASON23 0xff7f7f
# define SEASON31 0xA1856E
# define SEASON32 0x7A5230
# define SEASON33 0xE5E500
# define SEASON34 0xe57300
# define SEASON41 0xA1856E
# define SEASON42 0x7A5230
# define SEASON43 0xFFFFFF
# define SEASON44 0x0000FF

typedef struct
{
	double			x;
	double			y;
	int				colour;
}					t_point;

typedef struct
{
	double			r;
	double			g;
	double			b;
}					t_rgb;

typedef struct		s_i
{
	void			*img;
	char			*map;
	int				size_line;
	double			scale;
	double			zoom;
	double			move_x;
	double			move_y;
	double			iterations;
	double			a;
	double			size;
	double			c_rial;
	double			c_imegian;
	double			alpha;
	double			beta;
	int				season;
}					t_img;

typedef struct		s_koef
{
	double			fract;
	double			p;
	double			q;
	double			t;
}					t_koef;

typedef struct		s_print_struct
{
	int				steep1;
	int				steep2;
	double			x0;
	double			x1;
	double			y0;
	double			y1;
	int				**rgb;
}					t_print_struct;

typedef struct		s_f
{
	void			*mlx;
	void			*img_mlx;
	t_img			*img_struct;
	void			*w;
	char			c;
	int				flag_on;
	char			*string;
}					t_fractal;

/*
**	add_params.c
*/

t_fractal			*create_params(int size, char *fractals);
t_img				*add_valueses(int name);
void				create_zero_p_m(t_img **ptr);
void				create_zero_for_p(t_img **ptr);
void				copy_params(t_img *zero, t_img *img);

/*
**	additional.c
*/

char				*ft_toupper_str(char *str);
void				del_arrey(void **arrey, int size);
void				swap(double *x1, double *x2);
double				to_radians(double degrees);
int					what_fractal_is_it(char c);

/*
**	button_funk.c
*/

void				scale(t_fractal *f_s, int dir);
void				change_julia_mandelbrot_scale(int direction,
t_img *img, int n_f);
int					mouse_move(int x, int y, t_fractal *fractal_stuct);
int					button_funk(int button, int x, int y,
t_fractal *fractal_struct);

/*
**	image.c
*/

void				create_img_for_fractal(char *fractals);
void				create_img(t_img *img_struct, void *img_mlx);
void				create_size_for_img(t_fractal *f_s, char f);

/*
**	julia.c
*/

void				draw_julia(t_img *img, double move_dx,
double move_dy, double d_zoom);
int					count_iteration_julia(t_img *img, int y, int x, int i);
void				draw_julia_with_dif_set(t_fractal *f_s, int x, int y);

/*
**	key_funk.c
*/

int					my_key_funk(int keykode, t_fractal *f_s);
void				second_part(int keykode, t_fractal *fractal_struct);
void				move(t_fractal *f_s, int direction);

/*
**	main.c
*/

int					main(int argc, char **argv);
void				check_input(char fractal, char *string_input,
char **l_str_res);
char				*print_start(int *argc);
void				create_fractal(int c, t_img *img);
int					exit_x(void *par);

/*
**	maldebrot.c
*/
void				draw_mandelbrot(t_img *img, double move_x,
double move_y, double zoom);
void				x_loop_maldebrot(t_img *img, int x, int y, int i);
int					count_iteration_mandelbrot(t_img *img,
double pi, double pr, int i);
void				change_moving_julia_mandelbrot_move(int direction,
t_img *is, int n_f);

/*
**	print.c
*/

void				make_img_line(t_point *p1, t_point *p2, t_img *imege);
t_print_struct		*create_print_stuff(t_point *p1, t_point *p2);
void				print_img_line(t_print_struct *p_s,
t_img *img, float t, int x);
int					put_pixel_to_image(t_point *p, t_img *image);

/*
**	pyfagor.c
*/

void				draw_pyfagor_tree(t_img *img, double size_z,
double x, double y);
void				change_a(t_fractal *f_s, int dir);
void				draw_change_pyfagor_size(int direction, t_fractal *f_s);
void				change_iteration_pyfagor(t_fractal *f_s, int i);
void				draw_change_pyfagor_move(int direction, t_img *i_s);

/*
**	pyfagor_time.c
*/

void				get_colour_point(t_point *p1, t_point *p2, double size_z,
t_img *img);
void				winter_time(t_point *p1, t_point *p2, double i, double z);
void				fall_time(t_point *p1, t_point *p2, double i, double z);
void				summer_time(t_point *p1, t_point *p2, double i, double z);
void				spring_time(t_point *p1, t_point *p2, double i, double z);

/*
**	string_funk.c
*/

void				create_string(t_fractal *f_s, double size1);
double				pifagor_string(t_fractal *f_s);

/*
** colour.c
*/

int					get_colour(double h, double s, double v);
int					*c_rgb(int colour);
void				add_delta(double **matrix_colour, t_point *point);
void				del_delta(double **matrix_colour, t_point *point);
double				**create_gradient(int **rgb, double dx);
#endif
