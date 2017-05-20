#include "FRACTOL.h"

void	draw_mandelbrot(t_img *img, double move_x, double move_y, double zoom)
{
	int y;

    y = 0;
	img->move_x = move_x/zoom;
	img->move_y = move_y/zoom;
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
