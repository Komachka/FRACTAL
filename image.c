#include "FRACTOL.h"

void            create_img(t_img *img_struct, void *img_mlx)
{
    int     bit_per_pixel;
    int     size_line;
    int     endian;


    img_struct->map = mlx_get_data_addr(img_mlx, &bit_per_pixel,
                                        &size_line, &endian);
    img_struct->size_line = size_line;
    img_struct->iterations = 300;
    img_struct->zoom = 1;
    img_struct->move_x = 0;
    img_struct->move_y = 0;
}

void create_size_for_img(void **params, int i, char f)
{
    void *img1;
    t_img *img_struct1;
    int index;
    char *str;

    if (f == 'J')
        str = "Julia set";
    else  if(f == 'M')
        str = "Mandelbrot set";
    else
        str = "Pythagoras tree";
    index = get_index(i);
    img_struct1 = (t_img*)malloc(sizeof(t_img));
    img1 = mlx_new_image(params[0], WIDTH_I, HEIGHT_I);
    params[index] = img1;
    params[index + 1] = img_struct1;
    params[index + 2] = mlx_new_window(params[0], WIDTH_W, HEIGHT_W, str);

}

void **create_params(int size, char *fractals)
{

    int i;
    void    **params;
    void *mlx;

    mlx = mlx_init();
    params = malloc(sizeof(void*) * size * 4 + 1); // 1 = mlx 2 img_mlx 3 img_struct 4 window 5 fractal struct
    i = 1;
    size++;
    params[0] = mlx;
    while (i < size) {
        create_size_for_img(params, i, fractals[i - 1]);
        i++;
    }
    return (params);
}

void add_valueses(t_img *img_struct) {
    img_struct->a = M_PI/2;
    img_struct->size = 200;
    img_struct->move_x = WIDTH_W/2;
    img_struct->move_y = HEIGHT_W * 0.5;
    img_struct->iterations = 1;
}