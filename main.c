
#include "FRACTOL.h"


int     my_key_funk(int keykode, t_fractal *fractal_struct)
{
    if (keykode == 126)
        move(fractal_struct, UP);
    if (keykode == 125)
        move(fractal_struct, DOWN);
    if (keykode == 124)
        move(fractal_struct, LEFT);
    if (keykode == 123)
        move(fractal_struct, RIGHT);
    if (keykode == 49 && fractal_struct->flag_on == 1 && fractal_struct->c == 'J') {
        fractal_struct->flag_on = 0;
        return (0);
    }
    if (keykode == 49 && fractal_struct->flag_on == 0 && fractal_struct->c == 'J') {
        fractal_struct->flag_on = 1;
        return (0);
    }
    if (keykode == 69 && fractal_struct->c == 'P')
        change_a(fractal_struct, UP);
    if (keykode == 78 && fractal_struct->c == 'P')
        change_a(fractal_struct, DOWN);
    if (keykode == 18)
        fractal_struct->img_struct->season = 1;
    if (keykode == 19)
        fractal_struct->img_struct->season = 2;
    if (keykode == 20)
        fractal_struct->img_struct->season = 3;
    if (keykode == 21)
        fractal_struct->img_struct->season = 4;
    return (0);
}

void change_a(t_fractal *fractal_struct, int dir)
{
    t_img   *img_struct;

    img_struct = fractal_struct->img_struct;
    mlx_destroy_image(fractal_struct->mlx, fractal_struct->img_mlx);
    fractal_struct->img_mlx = mlx_new_image(fractal_struct->mlx, WIDTH_I, HEIGHT_I);
    create_img(img_struct, fractal_struct->img_mlx);
    if (dir == UP)
        img_struct->alpha  += 5;
    else if (dir == DOWN)
        img_struct->beta  += 5;
    if (img_struct->alpha > 360)
        img_struct->alpha = 0;
    if (img_struct->beta > 360)
        img_struct->beta = 0;
    draw_pyfagor_tree(img_struct, img_struct->size, img_struct->move_x, img_struct->move_y);
    img_struct->a = M_PI/2;
    mlx_put_image_to_window(fractal_struct->mlx, fractal_struct->w, fractal_struct->img_mlx, 0, 0);
    create_string(fractal_struct, 0);
}

void scale(t_fractal *fractal_struct, int direction) //////
{
    int n_f;
    char c;

    mlx_destroy_image(fractal_struct->mlx, fractal_struct->img_mlx);
    fractal_struct->img_mlx = mlx_new_image(fractal_struct->mlx, WIDTH_I, HEIGHT_I);
    create_img(fractal_struct->img_struct, fractal_struct->img_mlx);
    c = fractal_struct->c;
    n_f = what_fractal_is_it(c);

    if (n_f == JULIA || n_f == MALDEBROT)
        change_julia_mandelbrot_scale(direction, fractal_struct->img_struct, n_f);
    else if (n_f == PYFAGOR)
        draw_change_pyfagor_size(direction, fractal_struct);
    mlx_put_image_to_window(fractal_struct->mlx, fractal_struct->w, fractal_struct->img_mlx, 0, 0);
    create_string(fractal_struct, 0);

}

void draw_change_pyfagor_size(int direction, t_fractal *fractal_struct)
{
    double tmp_x;
    double tmp_y;
    double a_tmp;

    if (direction == UP)
        fractal_struct->img_struct->size += 50;
    else if (direction == DOWN)
        fractal_struct->img_struct->size -= 10;
    tmp_x = fractal_struct->img_struct->move_x;
    tmp_y = fractal_struct->img_struct->move_y;
    a_tmp = fractal_struct->img_struct->a;
    draw_pyfagor_tree(fractal_struct->img_struct, fractal_struct->img_struct->size, fractal_struct->img_struct->move_x, fractal_struct->img_struct->move_y);
    fractal_struct->img_struct->move_x = tmp_x;
    fractal_struct->img_struct->move_y = tmp_y;
    fractal_struct->img_struct->a = a_tmp;
}

void change_julia_mandelbrot_scale(int direction, t_img *img_struct, int n_f)
{
    double d_zoom;


    if (direction == DOWN)
        d_zoom = 1.1;
    else if (direction == UP)
        d_zoom = 0.9;
    img_struct->zoom *= d_zoom;
    if (n_f == JULIA)
        draw_julia(img_struct, img_struct->move_x, img_struct->move_y, d_zoom);
    else if (n_f == MALDEBROT)
        draw_mandelbrot(img_struct, img_struct->move_x, img_struct->move_y, d_zoom);


}

void    move(t_fractal *fractal_struct, int direction)
{
    t_img   *img_struct;
    int n_f;
    char c;

    img_struct = fractal_struct->img_struct;
    mlx_destroy_image(fractal_struct->mlx, fractal_struct->img_mlx);
    fractal_struct->img_mlx = mlx_new_image(fractal_struct->mlx, WIDTH_I, HEIGHT_I);
    create_img(img_struct, fractal_struct->img_mlx);
    c = fractal_struct->c;
    n_f = what_fractal_is_it(c);
    if (n_f == JULIA || n_f == MALDEBROT)
        change_moving_julia_mandelbrot_move(direction, img_struct, n_f);
    else if (n_f == PYFAGOR)
        draw_change_pyfagor_move(direction, img_struct);
    mlx_put_image_to_window(fractal_struct->mlx, fractal_struct->w, fractal_struct->img_mlx, 0, 0);
    create_string(fractal_struct, 0);
}




int what_fractal_is_it(char c)
{

    char f;

    f = c;
    if(f == 'J')
        return (JULIA);
    if (f == 'M')
        return (MALDEBROT);
    if (f == 'P')
        return (PYFAGOR);
    return 0;
}

int exit_x(void *par)
{
    free(par);
    par = NULL;
    exit(1);
}



int main(int argc, char **argv)
{
    char *fractals;
    int i;
    char *str;


    fractals = "JMP";
    ft_putstr("Fractals:\n- Julia set       (J)\n- Mandelbrot set  (M)\n- Pythagoras tree (p)\n");
    ft_putstr("Usage: ./fractol J\n       ./fractol J M\n");
    if (argc < 2 || argc > 4)
    {
        ft_putstr("Incorect Input");
        return (0);
    }
    argc--;
    char *str_res = ft_strnew(argc - 1); ////
    char *ptr = str_res; ////
    ft_memset(str_res,'/0', ft_strlen(str_res));
    while (argc > 0)
    {
        i = 0;
        while (fractals[i])
        {
            str = ft_strnew(1);
            str[0] = fractals[i];
            char *str2 = ft_toupper_str(argv[argc]);
            if (ft_strcmp(str, str2) == 0) {
                *str_res = fractals[i];
                str_res++;
            }
            ft_strdel(&str);
            i++;
        }
        argc--;
    }
    create_img_for_fractal(ptr);
    ft_strdel(&ptr);
}



void create_img_for_fractal(char *fractals) {

    int         size_f;
    t_fractal   *fractal_struct;
    char        c;

    size_f = (int)ft_strlen(fractals);
    if((fractal_struct = create_params(size_f, fractals)) == NULL)
        return;
    create_img(fractal_struct->img_struct, fractal_struct->img_mlx);
    c = fractal_struct->c;
    fractal_struct->flag_on = 0;
    create_fractal(c, fractal_struct->img_struct);

    mlx_put_image_to_window(fractal_struct->mlx, fractal_struct->w, fractal_struct->img_mlx, 0, 0);
    mlx_hook(fractal_struct->w, 17, 1L << 17, exit_x, fractal_struct);
    mlx_hook(fractal_struct->w, 2, 1L << 1, my_key_funk, fractal_struct);
    mlx_hook(fractal_struct->w, 6, 0, mouse_move, fractal_struct);
    mlx_mouse_hook(fractal_struct->w, button_funk, fractal_struct);
    create_string(fractal_struct, 0);
    mlx_loop(fractal_struct->mlx);
}

void create_string(t_fractal *fractal_struct, double size1)
{
    char *x;
    char *y;
    char *size;
    double x1;
    double y1;

    x1 = fractal_struct->img_struct->move_x;
    y1 = fractal_struct->img_struct->move_y;
    if (fractal_struct->c == 'P')
        size1 = pifagor_string(fractal_struct);
    else
        size1 = fractal_struct->img_struct->zoom * 1000;
    if (fractal_struct->c == 'J' || fractal_struct->c == 'M')
    {
        x1 *= 100;
        y1 *=100;
    }
    mlx_string_put(fractal_struct->mlx, fractal_struct->w, 10, 10, 0xFFFFFF, fractal_struct->string);
    x = ft_strjoin("x = ", ft_itoa((int)x1));
    mlx_string_put(fractal_struct->mlx, fractal_struct->w, 10, 30, 0xFFFFFF, x);
    y = ft_strjoin("y = ", ft_itoa((int)y1));
    mlx_string_put(fractal_struct->mlx, fractal_struct->w, 10, 50, 0xFFFFFF, y);
    size = ft_strjoin("size = ", ft_itoa((int)size1));
    mlx_string_put(fractal_struct->mlx, fractal_struct->w, 10, 70, 0xFFFFFF, size);
}

double pifagor_string(t_fractal *fractal_struct) {
    double size;
    double alpha;
    double beta;

    size = fractal_struct->img_struct->size;
    alpha = fractal_struct->img_struct->alpha;
    beta = fractal_struct->img_struct->beta;
    mlx_string_put(fractal_struct->mlx, fractal_struct->w, 10, 90, 0xFFFFFF, ft_strjoin("alpha = ", ft_itoa((int)alpha)));
    mlx_string_put(fractal_struct->mlx, fractal_struct->w, 10, 110, 0xFFFFFF, ft_strjoin("beta = ", ft_itoa((int)beta)));


    return (size);
}

void create_fractal(int c, t_img *img) {
    t_img *zero;

    if (c == 'J')
        zero = add_valueses(JULIA);
    else if (c == 'M')
        zero = add_valueses(MALDEBROT);
    else if (c == 'P')
        zero = add_valueses(PYFAGOR);
    copy_params(zero, img);
    if (c == 'J')
    {
        draw_julia(img, img->move_x, img->move_y, img->zoom);
    }
        else if (c == 'M')
        draw_mandelbrot(img, img->move_x, img->move_y, img->zoom);
    else if (c == 'P')
    {
        draw_pyfagor_tree(img, img->size, img->move_x, img->move_y);
        img->a = zero->a;
    }
    free(zero);
}

void copy_params(t_img *zero, t_img *img)
{
    img->zoom = zero->zoom;
    img->move_x = zero->move_x;
    img->move_y = zero->move_y;
    img->iterations =  zero->iterations;
    img->a = zero->a;
    img->size = zero->size;
    img->c_imegian = zero->c_imegian;
    img->c_rial = zero->c_rial;
    img->alpha = zero->alpha;
    img->beta = zero->beta;
    img->season = zero->season;
}


int mouse_move(int x, int y, t_fractal *fractal_stuct)
{
    if (fractal_stuct->flag_on == 1 && fractal_stuct->c == 'J')
        draw_julia_with_dif_set(fractal_stuct, x, y);
    return (0);
}

int button_funk(int button, int x, int y, t_fractal *fractal_struct)
{
    if (fractal_struct->c == 'P')
    {
        fractal_struct->img_struct->move_x = x;
        fractal_struct->img_struct->move_y = y + y/2;
        if (button == 1)
            change_iteration_pyfagor(fractal_struct, UP);
        else if (button == 2)
            change_iteration_pyfagor(fractal_struct, DOWN);
    }
    if (button == 4)
        scale(fractal_struct, UP);
    else if (button == 5)
        scale(fractal_struct, DOWN);
    return (0);

}

void change_iteration_pyfagor(t_fractal *fractal_struct, int i)
{
    int di;

    di = 1;
    t_img *img;
    t_img *zero;
    zero = add_valueses(PYFAGOR);
    img = fractal_struct->img_struct;
    if (i == UP && img->iterations != 1)
        fractal_struct->img_struct->iterations -= di;
    else if (i == DOWN)
        fractal_struct->img_struct->iterations += di;
    mlx_destroy_image(fractal_struct->mlx, fractal_struct->img_mlx);
    fractal_struct->img_mlx = mlx_new_image(fractal_struct->mlx, WIDTH_I, HEIGHT_I);
    create_img(fractal_struct->img_struct, fractal_struct->img_mlx);
    draw_pyfagor_tree(img, img->size, img->move_x, img->move_y);
    img->a = zero->a;
    free(zero);
    mlx_put_image_to_window(fractal_struct->mlx, fractal_struct->w, fractal_struct->img_mlx, 0, 0);
    create_string(fractal_struct, 0);
}

void draw_julia_with_dif_set(t_fractal *fractal_struct, int x, int y)
{

    double c_rial;
    double c_imegian;
    t_img *img;

    img = fractal_struct->img_struct;
    c_rial = (x - WIDTH_I/2) / (0.5 * fractal_struct->img_struct->zoom * WIDTH_I);
    c_imegian = (y - HEIGHT_I/2) / (0.5 * fractal_struct->img_struct->zoom * HEIGHT_I);
    img->move_x = 0;
    img->move_y = 0;
    fractal_struct->img_struct->c_rial = c_rial;
    fractal_struct->img_struct->c_imegian = c_imegian;
    mlx_destroy_image(fractal_struct->mlx, fractal_struct->img_mlx);
    fractal_struct->img_mlx = mlx_new_image(fractal_struct->mlx, WIDTH_I, HEIGHT_I);
    create_img(fractal_struct->img_struct, fractal_struct->img_mlx);
    draw_julia(img, img->move_x, img->move_y, img->zoom);
    mlx_put_image_to_window(fractal_struct->mlx, fractal_struct->w, fractal_struct->img_mlx, 0, 0);
    create_string(fractal_struct, 0);
}

































