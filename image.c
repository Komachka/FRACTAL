#include "FRACTOL.h"

void	create_img(t_img *img_struct, void *img_mlx)
{
	int		bit_per_pixel;
	int		size_line;
	int		endian;

	img_struct->map = mlx_get_data_addr(img_mlx, &bit_per_pixel,
										&size_line, &endian);
	img_struct->size_line = size_line;


}

void	create_size_for_img(t_fractal *fractal_stract, char f)
{
	void	*img1;
	t_img	*img_struct1;
	char	*str;
	char    c;

	c = f;
	if (c == 'J')
		str = "Julia set";
	else  if(c == 'M')
		str = "Mandelbrot set";
	else if (c == 'P')
		str = "Pythagoras tree";
	else
	{
		write(1, "Something go wrog\n", 17);
		exit(0);
	}
	img_struct1 = (t_img*)malloc(sizeof(t_img));
    img1 = mlx_new_image(fractal_stract->mlx, WIDTH_I, HEIGHT_I);
	fractal_stract->img_mlx = img1;
	fractal_stract->img_struct = img_struct1;
	fractal_stract->w = mlx_new_window(fractal_stract->mlx, WIDTH_W, HEIGHT_W, str);
	fractal_stract->c = c;
    fractal_stract->string = ft_strjoin(ft_strnew(0), str);
}

/*
**  coment1
** coment
*/

t_fractal	*create_params(int size, char *fractals)
{

	int		i;
	void	*mlx;
    int     id;
	t_fractal *fractal_struct;

    i = 1;
    while (i < size)
    {
        id = fork();
        if (id == 0) {
            fractals+=i;
            break;
        }
        i++;
    }
    mlx = mlx_init();
	fractal_struct = (t_fractal*)malloc(sizeof(t_fractal));
    fractal_struct->mlx = mlx;
    create_size_for_img(fractal_struct, *fractals);
    return (fractal_struct);
}

t_img	*add_valueses(int name)
{
	t_img *zero_struct;

    zero_struct = (t_img*)malloc(sizeof(t_img));
    if (name == PYFAGOR)
    {
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
    else
    {
        zero_struct->iterations = 300;
        zero_struct->zoom = 1;
        zero_struct->move_x = 0;
        zero_struct->move_y = 0;
        zero_struct->a = 0;
        zero_struct->size = 0;
        zero_struct->c_rial =C_RIAL;
        zero_struct->c_imegian = C_IMEGIAN;
    }
    if (name == MALDEBROT)
        zero_struct->zoom = 0.45;
    return (zero_struct);
}

void change_moving_julia_mandelbrot_move(int direction, t_img *img_struct, int n_f)
{
    printf("img_struct->move_x = %f\n", img_struct->move_x);
    printf("img_struct->move_y = %f\n", img_struct->move_y);
    double tmp_x;
    double tmp_y;

    if (direction == LEFT)
        img_struct->move_x = (img_struct->move_x - 0.10);
   else if (direction == RIGHT)
        img_struct->move_x = (img_struct->move_x + 0.10);
   else if (direction == DOWN)
        img_struct->move_y = (img_struct->move_y - 0.10);
   else if (direction == UP)
        img_struct->move_y = (img_struct->move_y + 0.10);
    printf("img_struct->move_x = %f\n", img_struct->move_x);
    printf("img_struct->move_y = %f\n", img_struct->move_y);
    tmp_x = img_struct->move_x;
    tmp_y = img_struct->move_y;
    if (n_f == JULIA)
        draw_julia(img_struct, img_struct->move_x, img_struct->move_y, img_struct->zoom);
    else if (n_f == MALDEBROT)
        draw_mandelbrot(img_struct, img_struct->move_x *img_struct->zoom, img_struct->move_y * img_struct->zoom, img_struct->zoom);
    img_struct->move_x = tmp_x;
    img_struct->move_y = tmp_y;
    printf("img_struct->move_x = %f\n", img_struct->move_x);
    printf("img_struct->move_y = %f\n\n", img_struct->move_y);
}



void draw_change_pyfagor_move(int direction, t_img *img_struct) {

    double tmp_x;
    double tmp_y;
    double dp;
    double a_tmp;

    dp = 10;
    if (direction == LEFT)
        img_struct->move_x += dp;
    else if (direction == RIGHT)
        img_struct->move_x -= dp;
    else if (direction == DOWN)
        img_struct->move_y += dp;
    else if (direction == UP)
        img_struct->move_y -= dp;
    tmp_x = img_struct->move_x;
    tmp_y = img_struct->move_y;
    a_tmp = img_struct->a;
    draw_pyfagor_tree(img_struct, img_struct->size, img_struct->move_x, img_struct->move_y);
    img_struct->move_x = tmp_x;
    img_struct->move_y = tmp_y;
    img_struct->a = a_tmp;
}