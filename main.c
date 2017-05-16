
#include "FRACTOL.h"

int size = 200;








int     my_key_funk(int keykode, void **param)
{

    if (keykode == 126)
        move(param, UP);
    if (keykode == 125)
        move(param, DOWN);
    if (keykode == 124)
        move(param, LEFT);
    if (keykode == 123)
        move(param, RIGHT);
    if (keykode == 69)
        scale(param, UP);
    if (keykode == 78)
        scale(param, DOWN);
    return (0);
}

void scale(void **param, int direction)
{
    t_img   *img_struct;
    img_struct = (t_img*)param[2];
    mlx_destroy_image(param[4], param[0]);
    param[0] = mlx_new_image(param[0], WIDTH_I, HEIGHT_I);
    create_img(img_struct, param[0]);
    if (direction == UP)
        draw_julia(img_struct, 0, 0, 1.5);
    else if (direction == DOWN)
        draw_julia(img_struct, 0, 0, 0.5);
    mlx_put_image_to_window(param[4], param[5], param[0], 0, 0);
}

void    move(void **param, int direction)
{
    t_img   *img_struct;

    img_struct = (t_img*)param[2];
    mlx_destroy_image(param[4], param[0]);
    param[0] = mlx_new_image(param[0], WIDTH_I, HEIGHT_I);
    create_img(img_struct, param[0]);
    if (direction == LEFT)
        draw_julia(img_struct, 0.25, 0, 1);
    else if (direction == RIGHT)
        draw_julia(img_struct, -0.25, 0, 1);
    else if (direction == DOWN)
        draw_julia(img_struct, 0, 0.25, 1);
    else if (direction == UP)
        draw_julia(img_struct, 0, -0.25, 1);
    mlx_put_image_to_window(param[4], param[5], param[0], 0, 0);

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
    void **params;
    int size_f;
    int i;
    int index;

    i = 1;
    size_f = (int)ft_strlen(fractals);
    if((params = create_params(size_f, fractals)) == NULL)
        return;
    while (i <= size_f)
    {
        index = get_index(i);
        create_img(params[index + 1], params[index]);
        if (fractals[i - 1] == 'J')
            draw_julia(params[index + 1], 0, 0, 1);
        else if (fractals[i - 1] == 'M')
            draw_mandelbrot(params[index + 1], 0, 0, 0.45);
        else if (fractals[i - 1] == 'P')
        {
            add_valueses(params[index + 1]);
            draw_pyfagor_tree(300, WIDTH_W / 2, HEIGHT_W * 0.75, params[index + 1]);
        }
            mlx_put_image_to_window(params[0], params[index + 2], params[index], 0, 0);
        i++;
    }

    //mlx_hook(params[size_f * 2 + 2], 17, 1L << 17, exit_x, params);
    //mlx_hook(params[size_f * 2 + 2], 2, 1L << 1, my_key_funk, params);

    //mlx_mouse_hook(params[size_f * 2 + 2], button_funk, params);
    //mlx_hook(params[size * 2 + 2], 6, 0, mouse_move, params);

    mlx_loop(params[0]);
    free(&params);


}












int mouse_move(int x, int y, void **param)
{
    if (0 <= x && x <= WIDTH_I - 1 && 0 <= y && y <= HEIGHT_W) {
        herak_julia_with_dif_set(param, x, y);
    }
    else if (WIDTH_I <= x && x <= WIDTH_W - 1) {

        t_img   *img_struct;

        img_struct = (t_img*)param[3];

        mlx_destroy_image(param[4], param[1]);
        param[1] = mlx_new_image(param[0], WIDTH_I, HEIGHT_I);
        create_img(img_struct, param[1]);
        dryw_pyfagor_tree_mouse(M_PI/2, size, x - WIDTH_I, y + HEIGHT_I/2, img_struct,  180 - (x - HEIGHT_I)* 360 / HEIGHT_I );
        mlx_put_image_to_window(param[4], param[5], param[1], WIDTH_I, 0);
    }
    return (0);
}

int button_funk(int button, int x, int y, void **param)
{

    //printf("button = %d\n", button);
    if (button == 4 && 0 <= x && x <= WIDTH_I - 1)
        scale(param, UP);
    else if (button == 5 && 0 <= x && x <= WIDTH_I - 1)
        scale(param, DOWN);
    else if (button == 4 && WIDTH_I <= x && x <= WIDTH_W - 1)
    {
        size -= 10;
        t_img   *img_struct;
        img_struct = (t_img*)param[3];
        mlx_destroy_image(param[4], param[1]);
        param[1] = mlx_new_image(param[1], WIDTH_I, HEIGHT_I);
        create_img(img_struct, param[1]);
        dryw_pyfagor_tree_mouse(M_PI/2, size, x - WIDTH_I, y + HEIGHT_I/2, img_struct,  180 - (x - HEIGHT_I)* 360 / HEIGHT_I );
        mlx_put_image_to_window(param[4], param[5], param[1], WIDTH_I, 0);
        return (0);
    } else if (button == 5 && WIDTH_I <= x && x <= WIDTH_W - 1)
    {
        size += 10;
        t_img   *img_struct;
        img_struct = (t_img*)param[3];
        mlx_destroy_image(param[4], param[1]);
        param[1] = mlx_new_image(param[1], WIDTH_I, HEIGHT_I);
        create_img(img_struct, param[1]);
        dryw_pyfagor_tree_mouse(M_PI/2, size, x - WIDTH_I, y + HEIGHT_I/2, img_struct,  180 - (x - HEIGHT_I)* 360 / HEIGHT_I );
        mlx_put_image_to_window(param[4], param[5], param[1], WIDTH_I, 0);
        return (0);
    }
    else if (button == 1 && 0 <= x && x <= WIDTH_I - 1) {

        herak_julia_with_dif_set(param, x, y);
        return (0);
    }
   /* else if (button == 1 && WIDTH_I <= x && x <= WIDTH_W - 1) {

        t_img   *img_struct;

        img_struct = (t_img*)param[2];
        mlx_destroy_image(param[4], param[0]);
        param[0] = mlx_new_image(param[0], WIDTH_I, HEIGHT_I);
        create_img(img_struct, param[0]);

        dryw_pyfagor_tree_mouse(M_PI/2, size, x - HEIGHT_I, y - HEIGHT_I, img_struct,  (x - HEIGHT_I)* 180 / HEIGHT_I );
        mlx_put_image_to_window(param[4], param[5], param[0], 0, 0);

        return (0);
    }*/

    return (0);

}

void herak_julia_with_dif_set(void **param, int x, int y)
{
    t_img   *img_struct;

    img_struct = (t_img*)param[2];
    mlx_destroy_image(param[4], param[0]);
    param[0] = mlx_new_image(param[0], WIDTH_I, HEIGHT_I);
    create_img(img_struct, param[0]);

    herack_julia_key(img_struct, 0, 0, 1, x, y);
    mlx_put_image_to_window(param[4], param[5], param[0], 0, 0);
}

void herack_julia_key(t_img *img, int d_move_x, int d_move_y, int d_zoom, double n_x, double n_y)
{
    int max_iteration = 300;
    //double c_rial = -0.79;

    //double c_imegian = 0.15;


    double new_rial =0;
    double new_imegian;


    double old_real = 0;
    double old_imegien = 0;
    int x = 0;
    int y = 0;
    static double zoom = 1;
    int color = 0;
    static double move_x = 0;
    static double move_y = 0;

    move_x += d_move_x / zoom;
    move_y += d_move_y / zoom;
    zoom *= d_zoom;
    t_point *p = (t_point*)malloc(sizeof(t_point));
    double c_rial = (n_x - WIDTH_I/2) / (0.5 * zoom * WIDTH_I);
    double c_imegian = (n_y - HEIGHT_I/2) / (0.5 * zoom * HEIGHT_I);
    //printf("x = %f y = %f c_rial = %f c_imegian = %f\n",n_x, n_y, c_rial, c_imegian);

    while (y < HEIGHT_I)
    {
        x = 0;
        while (x < WIDTH_I)
        {
            new_rial =   (x - WIDTH_I/2) / (0.5 * zoom * WIDTH_I) + move_x;
            new_imegian =  (y - HEIGHT_I/2) / (0.5 * zoom * HEIGHT_I) + move_y;
            int i = 1;
            while (i < max_iteration)
            {
                old_real = new_rial;
                old_imegien = new_imegian;
                new_rial = old_real * old_real  - old_imegien * old_imegien + c_rial;
                new_imegian = 2 * old_real * old_imegien + c_imegian;
                if ((new_rial * new_rial + new_imegian * new_imegian) > 4) break;
                i++;

            }
            color = get_colour(i % 256, 255, 255 * (i < max_iteration)); // цвет, насыщеность, яркость
            p->colour = color;
            p->x = x;
            p->y = y;
            put_pixel_to_image(p, img);
            //printf("%d%%256 = %d \n ",i, i % 256);


            //color = get_colour(i % 256, 255, 100);

            //mlx_pixel_put(mlx, w, x, y, color);
            x++;

        }
        y++;
    }
    free(p);
}




















void dryw_pyfagor_tree_mouse(double a, double size, double x, double y, t_img *img, double degree) // size = 200; a = pi/2
{
    t_point *p1;
    t_point *p2;

    p1 = (t_point*)malloc(sizeof(t_point));
    p2 = (t_point*)malloc(sizeof(t_point));
    if (size > 1)
    {
        size *= 0.7;
        p1->x = x;
        p1->y = y;
        p2->x = x + size * cos(a);
        p2->y = y - size * sin(a);
        p1->colour = 0xFFFF00;
        p2->colour = 0x0000FF;
        make_img_line(p1, p2, img);
        x = x + size * cos(a);
        y = y - size * sin(a);
        dryw_pyfagor_tree_mouse(a - to_radians(degree), size, x, y, img, degree);
        dryw_pyfagor_tree_mouse(a + to_radians(degree), size, x, y, img, degree);
    }
}















