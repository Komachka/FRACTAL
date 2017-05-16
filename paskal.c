#include "FRACTOL.h"

void	draw_pyfagor_tree(double size_z, double x, double y, t_img *img)
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
		p2->x = x + size_z * cos(a1);
		p2->y = y - size_z * sin(a1);
		get_colour_point(p1, p2, size_z, img->iterations);
		make_img_line(p1, p2, img);
		x = x + size_z * cos(a1);
		y = y - size_z * sin(a1);
		a1 = img->a;
		img->a = img->a + to_radians(45);
		draw_pyfagor_tree(size_z, x, y, img);
		img->a = a1 - to_radians(30);
		draw_pyfagor_tree(size_z, x, y, img);
	}
}

void	get_colour_point(t_point *p1, t_point *p2, double size_z,
double iterations)
{
	if (size_z / 2 > iterations)
	{
		p1->colour = 0xA1856E;
		p2->colour = 0x7A5230;
	}
	else
	{
		p1->colour = 0x3F553F;
		p2->colour = 0x4ca64c;
	}
}
