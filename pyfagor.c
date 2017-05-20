#include "FRACTOL.h"


void spring_time(t_point *p1, t_point *p2, double iterations, double z);

void summer_time(t_point *p1, t_point *p2, double iterations, double z);

void fall_time(t_point *p1, t_point *p2, double iterations, double z);

void winter_time(t_point *p1, t_point *p2, double iterations, double z);

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
        p2->x = x =  x + size_z * cos(a1);
        p2->y = y = y - size_z * sin(a1);
        get_colour_point(p1, p2, size_z, img);
        make_img_line(p1, p2, img);
        a1 = img->a;
        img->a = img->a + to_radians(img->alpha);
        draw_pyfagor_tree(img, size_z, x, y);
        img->a = a1 - to_radians(img->beta);
        draw_pyfagor_tree(img, size_z, x, y);
    }

}








void	get_colour_point(t_point *p1, t_point *p2, double size_z,
t_img *img)
{
	double iterations;

    iterations = img->iterations;
    if (img->season == 1)
        spring_time(p1, p2, iterations, size_z);
    else if (img->season == 2)
        summer_time(p1, p2, iterations, size_z);
    else if (img->season == 3)
        fall_time(p1, p2, iterations, size_z);
    else if (img->season == 4)
        winter_time(p1, p2, iterations, size_z);

}

void winter_time(t_point *p1, t_point *p2, double iterations, double z) {
    if (z / 2 > iterations)
    {
        p1->colour = SEASON41;
        p2->colour = SEASON42;
    }
    else
    {
        p1->colour = SEASON43;
        p2->colour = SEASON44;
    }
}

void fall_time(t_point *p1, t_point *p2, double iterations, double z) {
    if (z / 2 > iterations)
    {
        p1->colour = SEASON31;
        p2->colour = SEASON32;
    }
    else
    {
        p1->colour = SEASON33;
        p2->colour = SEASON34;
    }
}

void summer_time(t_point *p1, t_point *p2, double iterations, double z) {
    if (z / 2 > iterations)
    {
        p1->colour = SEASON21;
        p2->colour = SEASON22;
    }
    else
    {
        p1->colour = SEASON23;
        p2->colour = SEASON24;
    }
}

void spring_time(t_point *p1, t_point *p2, double iterations, double z)
{
    if (z / 2 > iterations)
    {
        p1->colour = SEASON11;
        p2->colour = SEASON12;
    }
    else
    {
        p1->colour = SEASON13;
        p2->colour = SEASON14;
    }
}
