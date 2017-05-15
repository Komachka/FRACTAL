
#include "FRACTOL.h"

int size = 200;

int count_iteration_julia(t_img *img, int y, int x, int i);

        void dryw_pyfagor_tree(double size_z, double x, double y, t_img *img);
char *ft_toupper_str(char *str);

void create_img_for_fractal(char *fractals);

void **fractals_size(int f);
int get_index(int i);

void **create_params(int size, char *str);

void create_size_for_img(void **params, int i, double width_i, char f);

int get_y(int size_f, int i);

int get_x(int size_f, int i);

void check_dooble(char *fractals);


void add_valueses(t_img *img_struct);

void get_colour_point(t_point *p1, t_point *p2, double size_z, double iterations);



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
    char *str_res = ft_strnew(argc - 1);
    char *ptr = str_res;
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
            herack_julia(params[index + 1], 0, 0, 1);
        else if (fractals[i - 1] == 'M')
            herack_mandelbrot(params[index + 1], 0, 0, 1);
        else if (fractals[i - 1] == 'P')
        {
            add_valueses(params[index + 1]);
            dryw_pyfagor_tree(300, WIDTH_W / 2, HEIGHT_W * 0.75, params[index + 1]);
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

void add_valueses(t_img *img_struct) {
    img_struct->a = M_PI/2;
    img_struct->size = 200;
    img_struct->move_x = WIDTH_W/2;
    img_struct->move_y = HEIGHT_W * 0.5;
    img_struct->iterations = 1;
}


void **create_params(int size, char *fractals)
{

    int i;
    void    **params;
    void *mlx;

    double width_i;

    width_i = WIDTH_W/size;
    mlx = mlx_init();
    params = malloc(sizeof(void*) * size * 4 + 1); // 1 = mlx 2 img_mlx 3 img_struct 4 window 5 fractal struct
    i = 1;
    size++;
    params[0] = mlx;
    while (i < size) {
        create_size_for_img(params, i, width_i, fractals[i - 1]);
        i++;
    }
    return (params);
}

void create_size_for_img(void **params, int i, double width_i, char f)
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

int get_index(int i)
{
    int index;

    index = 1;
    if (i == 1)
        index = 1;
    else if (i == 2)
        index = 4;
    else if (i == 3)
        index = 7;
    return (index);
}
char *ft_toupper_str(char *str) {
    int i;

    i = 0;
    while (str[i])
    {
        str[i] = (char)ft_toupper(str[i]);
        i++;
    }
    return (str);

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

void herack_mandelbrot(t_img *img, double move_x, double move_y, double zoom)
{
    double pr, pi;
    //int max_iteration = 300;
    //double c_rial = - 0.7;
    double c_rial = -0.7;
    double c_imegian = 0.27015;


    double new_rial =0;
    double new_imegian;


    double old_real = 0;
    double old_imegien = 0;
    int x = 0;
    int y = 0;
    int color = 0;

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
            while (i < img->iterations)
            {
                old_real = new_rial;
                old_imegien = new_imegian;
                new_rial = old_real * old_real - old_imegien * old_imegien + pr;
                new_imegian = 2 * old_real * old_imegien + pi;
                if ((new_rial * new_rial + new_imegian * new_imegian) > 4) break;
                i++;

            }
            color = get_colour(i % 256, 255, 255 * (i < img->iterations)); // цвет, насыщеность, яркость
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



int get_colour(double h, double s, double v)
{
    t_rgb rgb;
    t_koef koef;

    (h == 360) ? (h = 0.):(h /= 60.);
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
    return  ((int)rgb.r +
            ((int)rgb.g << 8) + ((int)rgb.b << 16));
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
    img_struct->iterations = 300;
    img_struct->zoom = 1;
    img_struct->move_x = 0;
    img_struct->move_y = 0;
}

void herack_julia(t_img *img, double move_dx, double move_dy, double d_zoom)
{
    t_point *p;
    int x;
    int y;
    int i;

    y = 0;
    p = (t_point*)malloc(sizeof(t_point));
    img->move_x += move_dx / img->zoom;
    img->move_y += move_dy / img->zoom;
    img->zoom *= d_zoom;
    while (y < HEIGHT_I)
    {
        x = 0;
        while (x < WIDTH_I)
        {
            i = count_iteration_julia(img, y, x, 1);
            p->colour = get_colour(i % 256, 255, 255 * (i < img->iterations)); // цвет, насыщеность, яркость;
            p->x = x;
            p->y = y;
            put_pixel_to_image(p, img);
            x++;
        }
        y++;
    }
    free(p); // если че не будем фришить
}

int count_iteration_julia(t_img *img, int y, int x, int i)
{
    static double new_rial = 0;
    static double new_imegian;
    static double old_real = 0;
    static double old_imegien = 0;

    new_rial =   (x - WIDTH_I/2) / (0.5 * img->zoom * WIDTH_I) + img->move_x;
    new_imegian =  (y - HEIGHT_I/2) / (0.5 * img->zoom * HEIGHT_I) + img->move_y;
    while (i < img->iterations)
        {
            old_real = new_rial;
            old_imegien = new_imegian;
            new_rial = old_real * old_real  - old_imegien * old_imegien + C_RIAL;
            new_imegian = 2 * old_real * old_imegien + C_IMEGIAN;
            if ((new_rial * new_rial + new_imegian * new_imegian) > 4) break;
            i++;

        }
    return (i);
}


void dryw_pyfagor_tree(double size_z, double x, double y, t_img *img)
{
    t_point *p1;
    t_point *p2;
    double a1;

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
        dryw_pyfagor_tree(size_z, x, y, img);
        img->a = a1 - to_radians(30);
        dryw_pyfagor_tree(size_z, x, y, img);
    }
}

void get_colour_point(t_point *p1, t_point *p2, double size_z, double iterations) {
    if (size_z/2 > iterations) {
        p1->colour = 0xA1856E;
        p2->colour = 0x7A5230;
    } else
    {
        p1->colour = 0x3F553F;
        p2->colour = 0x4ca64c;
    }
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



void    print_img_line(t_print_struct *print_stuff, t_img *img, float t, int x)
{
    int     y;
    t_point *point;
    double  **matrix_colour;


    point = (t_point*)malloc(sizeof(t_point));
    matrix_colour = create_gradient(print_stuff->rgb,
                                    print_stuff->x1 - print_stuff->x0);
    x = (int)print_stuff->x0;
    while (x <= print_stuff->x1)
    {
        (print_stuff->steep2 == 1) ? del_delta(matrix_colour, point) :
        add_delta(matrix_colour, point);
        t = (float)((x - print_stuff->x0) /
                    (float)(print_stuff->x1 - print_stuff->x0));
        y = (int)(print_stuff->y0 * (1.0 - t) + print_stuff->y1 * t);
        point->x = (print_stuff->steep1) ? y : x;
        point->y = (print_stuff->steep1) ? x : y;
        put_pixel_to_image(point, img);
        x++;
    }
    del_arrey((void **)matrix_colour, 3);
}

void    make_img_line(t_point *p1, t_point *p2, t_img *imege)
{
    t_print_struct  *print_struct;

    if ((print_struct = create_print_stuff(p1, p2)) == NULL)
        return ;
    if (print_struct->x1 - print_struct->x0 == 0)
        return ;
    if (fabs(print_struct->x0 - print_struct->x1) < fabs(print_struct->y0 - print_struct->y1))
    {
        swap(&print_struct->x0, &print_struct->y0);
        swap(&print_struct->x1, &print_struct->y1);
        print_struct->steep1 = 1;
    }
    if (print_struct->x0 > print_struct->x1)
    {
        swap(&print_struct->x0, &print_struct->x1);
        swap(&print_struct->y0, &print_struct->y1);
        print_struct->steep2 = 1;
    }
    print_img_line(print_struct, imege, 0, 0);
    del_arrey((void **)print_struct->rgb, 2);
}

void    swap(double *x1, double *x2)
{
    double  i;
    double  j;

    i = *x1;
    j = *x2;
    *x1 = j;
    *x2 = i;
}

void    del_arrey(void **arrey, int size)
{
    int i;

    i = 0;
    while (i < size)
    {
        if (arrey[i] != NULL)
            free(arrey[i]);
        i++;
    }
    if (arrey != NULL)
        free(arrey);
}



t_print_struct  *create_print_stuff(t_point *p1, t_point *p2)
{
    t_print_struct  *print_struct;

    if ((print_struct = (t_print_struct*)malloc(sizeof(t_print_struct)))
        == NULL)
        return (NULL);
    print_struct->steep1 = 0;
    print_struct->steep2 = 0;
    print_struct->x0 = p1->x;
    print_struct->x1 = p2->x;
    print_struct->y0 = p1->y;
    print_struct->y1 = p2->y;
    if ((print_struct->rgb = (int**)malloc(sizeof(int*) * 2)) == NULL)
        return (NULL);
    print_struct->rgb[0] = c_rgb(p1->colour);
    print_struct->rgb[1] = c_rgb(p2->colour);
    return (print_struct);
}

double  to_radians(double degrees)
{
    return (degrees / 180.0 * M_PI);
}