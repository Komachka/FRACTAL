#include <mlx.h>
#include <math.h>

#define WIDTH_W 2000
#define HEIGHT_W 1000

#define WIDTH_I WIDTH_W/2
#define HEIGHT_I HEIGHT_W

#define UP 1
#define DOWN -1
#define LEFT -2
#define RIGHT 2



#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


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

} t_img;


void    move(void **param, int direction);
int     my_key_funk(int keykode, void **param);
int get_colour(double H, double S, double V);
void create_img(t_img *img_struct, void *img_mlx);

void herack_julia(t_img *img, double move_dx, double move_dy, double d_zoom);

void herack_mandelbrot(t_img *img, double move_x, double move_y, double zoom);
int exit_x(void *par);
int button_funk(int button, int x, int y, void *param);


void scale(void **param, int direction);

void herak_julia_with_dif_set(void **param, int x, int y);

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
        herack_julia(img_struct, 0, 0, 1.5);
    else if (direction == DOWN)
        herack_julia(img_struct, 0, 0, 0.5);
    mlx_put_image_to_window(param[4], param[5], param[0], 0, 0);
}


/*params[0] = img1;
params[1] = img2;
params[2] = img_struct1;
params[3] = img_struct2;
params[4] = mlx;*/

void    move(void **param, int direction)
{



    t_img   *img_struct;

    img_struct = (t_img*)param[2];
    mlx_destroy_image(param[4], param[0]);
    param[0] = mlx_new_image(param[0], WIDTH_I, HEIGHT_I);
    create_img(img_struct, param[0]);
    if (direction == LEFT)
        herack_julia(img_struct, 0.25, 0, 1);
    else if (direction == RIGHT)
        herack_julia(img_struct, -0.25, 0, 1);
    else if (direction == DOWN)
        herack_julia(img_struct, 0, 0.25, 1);
    else if (direction == UP)
        herack_julia(img_struct, 0, -0.25, 1);
    mlx_put_image_to_window(param[4], param[5], param[0], 0, 0);

}

int exit_x(void *par)
{
    free(par);
    par = NULL;
    exit(1);
}



int main()
{
    void *mlx;
    void *w;
    void *img1;
    void *img2;
    t_img *img_struct1;
    t_img *img_struct2;
    void    **params;

    img_struct1 = (t_img*)malloc(sizeof(t_img));
    img_struct2 = (t_img*)malloc(sizeof(t_img));
    params = malloc(sizeof(void*) * 6);
    mlx = mlx_init();
    w = mlx_new_window(mlx, WIDTH_W, HEIGHT_W, "FRACTAL");
    img1 = mlx_new_image(mlx, WIDTH_I, HEIGHT_I);
    img2 = mlx_new_image(mlx, WIDTH_I, HEIGHT_I);
    create_img(img_struct1, img1);



    herack_julia(img_struct1, 0, 0, 1);
    create_img(img_struct2, img2);
    herack_mandelbrot(img_struct2, 0, 0, 1);
    params[0] = img1;
    params[1] = img2;
    params[2] = img_struct1;
    params[3] = img_struct2;
    params[4] = mlx;
    params[5] = w;
    mlx_put_image_to_window(mlx, w, img1, 0, 0);
    mlx_put_image_to_window(mlx, w, img2, WIDTH_I, 0);
    mlx_hook(w, 17, 1L << 17, exit_x, params);
    mlx_hook(w, 2, 1L << 1, my_key_funk, params);

    mlx_mouse_hook(w, button_funk, params);

    mlx_loop(mlx);

}

int button_funk(int button, int x, int y, void *param)
{
    printf("button = %d\n", button);
    if (button == 4 && 0 <= x && x <= WIDTH_I - 1)
        scale(param, UP);
    else if (button == 5 && 0 <= x && x <= WIDTH_I - 1)
        scale(param, DOWN);
   // else if (button == 1)
    //    herak_julia_with_dif_set(param, x/100, y/100);
}

void herak_julia_with_dif_set(void **param, int x, int y)
{
    t_img   *img_struct;

    img_struct = (t_img*)param[2];
    mlx_destroy_image(param[4], param[0]);
    param[0] = mlx_new_image(param[0], WIDTH_I, HEIGHT_I);
    create_img(img_struct, param[0]);

    herack_julia(img_struct, 0, -0.25, 1);
    mlx_put_image_to_window(param[4], param[5], param[0], 0, 0);
}

void herack_mandelbrot(t_img *img, double move_x, double move_y, double zoom)
{
    double pr, pi;
    int max_iteration = 300;
    //double c_rial = - 0.7;
    double c_rial = -0.7;
    double c_imegian = 0.27015;


    double new_rial =0;
    double new_imegian;


    double old_real = 0;
    double old_imegien = 0;
    int x = 0;
    int y = 0;
    //double zoom = 1;
    int color = 0;
    //double move_x = 0;
   // double move_y = 0;
    t_point *p = (t_point*)malloc(sizeof(t_point));
    while (y < HEIGHT_I)
    {
        x = 0;
        while (x < WIDTH_I)
        {
            pr = (x - WIDTH_I/2) / (0.5 * zoom * WIDTH_I) + move_x;
            pi = (y - HEIGHT_I/2) / (0.5 * zoom * HEIGHT_I) + move_y;
            new_rial = new_imegian = old_imegien = old_real = 0;
            int i = 1;
            while (i < max_iteration)
            {
                old_real = new_rial;
                old_imegien = new_imegian;
                new_rial = old_real * old_real - old_imegien * old_imegien + pr;
                new_imegian = 2 * old_real * old_imegien + pi;
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


int get_colour(double H, double S, double V) {


    t_rgb rgb;

    double  fract;
    double P, Q, T;
    (H == 360) ? (H = 0.):(H /= 60.);
    fract = H - ceil(H);

    P = V * (1. - S);
    Q = V * (1. - S * fract);
    T = V * (1. - S * (1. - fract));

    if (0. <= H && H < 1.)
        rgb = (t_rgb){.r = V, .g = T, .b = P};
    else if (1. <= H && H < 2.)
        rgb = (t_rgb){.r = Q, .g = V, .b = P};
    else if (2. <= H && H < 3.)
        rgb = (t_rgb){.r = P, .g = V, .b = T};
    else if (3. <= H && H < 4.)
        rgb = (t_rgb){.r = P, .g = Q, .b = V};
    else if (4. <= H && H < 5.)
        rgb = (t_rgb){.r = T, .g = P, .b = V};
    else if (5. <= H && H < 6.)
        rgb = (t_rgb){.r = V, .g = P, .b = Q};
    else
        rgb = (t_rgb){.r = 0., .g = 0., .b = 0.};
    return  (int)rgb.r +
                    ((int)rgb.g << 8) + ((int)rgb.b << 16);

}

int     put_pixel_to_image(t_point *p, t_img *image)
{
    int     col;
    int     k;
    char    *map;
    int     size_line;

    col = p->colour;
    map = image->map;
    size_line = image->size_line;
    if (p->x >= WIDTH_I || p->y >= HEIGHT_I || p->x < 0 || p->y < 0)
        return (-1);
    k = (int)(ceil(p->y) * size_line + ceil(p->x) * 4);
    if (k >= HEIGHT_I * size_line * 4 - 1)
        return (-1);
    else if (k < 0)
        return (-1);
    map[k] = (unsigned char)(col & 0xFF);
    k++;
    map[k] = (unsigned char)(col >> 8 & 0xFF);
    k++;
    map[k] = (unsigned char)(col >> 16 & 0xFF);
    return (0);
}

void            create_img(t_img *img_struct, void *img_mlx)
{
    int     bit_per_pixel;
    int     size_line;
    int     endian;


    img_struct->map = mlx_get_data_addr(img_mlx, &bit_per_pixel,
                                        &size_line, &endian);
    img_struct->size_line = size_line;


}

void herack_julia(t_img *img, double move_dx, double move_dy, double d_zoom)
{
    int max_iteration = 300;
    //double c_rial = -0.79;
    double c_rial = -0.7;
    double c_imegian = 0.27015;
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

    move_x += move_dx / zoom;
    move_y += move_dy / zoom;
    zoom *= d_zoom;
    t_point *p = (t_point*)malloc(sizeof(t_point));
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