#include "FRACTOL.h"

void	draw_julia(t_img *img, double move_dx, double move_dy, double d_zoom)
{
	t_point *p;
	int		x;
	int		y;
	int		i;

	y = 0;
	p = (t_point*)malloc(sizeof(t_point));
	img->move_x = move_dx/d_zoom;
	img->move_y = move_dy/d_zoom;
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

int		get_colour(double h, double s, double v)
{
	t_rgb	rgb;
	t_koef	koef;

	(h == 360) ? (h = 0.) : (h /= 60.);
	koef.fract = h - ceil(h);
	koef.p = v * (1. - s);
	koef.q = v * (1. - s * koef.fract);
	koef.t = v * (1. - s * (1. - koef.fract));
	if (0. <= h && h < 1.)
		rgb = (t_rgb){.r = v, .g = koef.t, .b = koef.p};
	else if (1. <= h && h < 2.)
		rgb = (t_rgb){.r = koef.q, .g = v, .b = koef.p};
	else if (2. <= h && h < 3.)
		rgb = (t_rgb){.r = koef.p, .g = v, .b = koef.t};
	else if (3. <= h && h < 4.)
		rgb = (t_rgb){.r = koef.p, .g = koef.q, .b = v};
	else if (4. <= h && h < 5.)
		rgb = (t_rgb){.r = koef.t, .g = koef.p, .b = v};
	else if (5. <= h && h < 6.)
		rgb = (t_rgb){.r = v, .g = koef.p, .b = koef.q};
	else
		rgb = (t_rgb){.r = 0., .g = 0., .b = 0.};
	return ((int)rgb.r +
((int)rgb.g << 8) + ((int)rgb.b << 16));
}

