//
// Created by Kateryna Storozh on 5/12/17.
//

#ifndef FRACTOL_FRACTOL_H
#define FRACTOL_FRACTOL_H

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

#define WIDTH_W 1000
#define HEIGHT_W 1000

#define WIDTH_I WIDTH_W
#define HEIGHT_I HEIGHT_W

#define UP 1
#define DOWN -1
#define LEFT -2
#define RIGHT 2

#define C_RIAL -0.7
#define C_IMEGIAN 0.27015



typedef struct
{
    double       x;
    double       y;
    int         colour;
}t_point;

typedef struct
{
    double r;
    double g;
    double b;
} t_rgb;


typedef struct
{
    void        *img;
    char        *map;
    int         size_line;
    double      scale;

    double zoom;
    double move_x;
    double move_y;
    double iterations;
    double a;
    double size;


} t_img;

typedef struct s_koef
{
    double fract;
    double p;
    double q;
    double t;
}t_koef;


typedef struct  s_print_struct
{
    int         steep1;
    int         steep2;
    double      x0;
    double      x1;
    double      y0;
    double      y1;
    int         **rgb;
}              t_print_struct;



void    move(void **param, int direction);
int     my_key_funk(int keykode, void **param);
int get_colour(double h, double s, double v);
void create_img(t_img *img_struct, void *img_mlx);

void herack_julia(t_img *img, double move_dx, double move_dy, double d_zoom);

void herack_mandelbrot(t_img *img, double move_x, double move_y, double zoom);
int exit_x(void *par);
int button_funk(int button, int x, int y, void **param);

void scale(void **param, int direction);

void herak_julia_with_dif_set(void **param, int x, int y);

void herack_julia_key(t_img *img, int d_move_x, int d_move_y, int d_zoom, double n_x, double n_y);
//int mouse_move(int x, int y, void *param);
int mouse_move(int x, int y, void **param);


double	**create_gradient(int **rgb, double dx);
void	del_delta(double **matrix_colour, t_point *point);
void	add_delta(double **matrix_colour, t_point *point);
int		*c_rgb(int colour);



t_print_struct  *create_print_stuff(t_point *p1, t_point *p2);
void    del_arrey(void **arrey, int size);
void    swap(double *x1, double *x2);
void    make_img_line(t_point *p1, t_point *p2, t_img *imege);
void    print_img_line(t_print_struct *print_stuff, t_img *img, float t, int x);
//void dryw_pyfagor_tree(t_img *img);

double  to_radians(double degrees);

void dryw_pyfagor_tree_mouse(double a, double size, double x, double y, t_img *img, double degree);

#endif //FRACTOL_FRACTOL_H
