#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define WIDTH 1920 * 1
#define HEIGHT 1080 * 1
#define M_PI 3.14159265358979323846

int res_downgrade = 3;

void *mlx;
void *win;
void *img;
void *scaled_img;
int img_width, img_height;
int scaled_img_width, scaled_img_height;
char *data_addr;
char *scaled_data_addr;
int bpp, size_line, endian;
int scaled_bpp, scaled_size_line, scaled_endian;

double scale_factor = 1;
double angle = 0;

bool go_up = true;

typedef struct s_render
{
    void *img_ptr;
    char *img_data;

    int bits_per_pixel;
    int size_line;
    int endian;

} t_render;

t_render *render(t_render *ren)
{
    static t_render *r;

    if (ren)
        r = ren;

    return r;
}

void *load_image()
{
    char *relative_path = "./assets/wall2.xpm";
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    if (!img)
    {
        printf("Error loading image\n");
        exit(1);
    }
    data_addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    printf("Image loaded: width=%d, height=%d, bpp=%d, size_line=%d\n", img_width, img_height, bpp, size_line);
    return img;
}

void insert_pixel(int x, int y, int color)
{
    t_render *r = render(NULL);

    r->img_data = mlx_get_data_addr(r->img_ptr, &r->bits_per_pixel, &r->size_line, &r->endian);
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return;

    int index = y * r->size_line + x * r->bits_per_pixel / 8;

    r->img_data[index] = color & 0xFF;            // Blue component
    r->img_data[index + 1] = (color >> 8) & 0xFF; // Green component
    r->img_data[index + 2] = (color >> 16) & 0xFF; // Red component
}

void view_center()
{
    int i = 0;
    while (i < WIDTH)
    {
        mlx_pixel_put(mlx, win, i, HEIGHT / 2, 0x0000FF00);
        i++;
    }

    i = 0;
    while (i < HEIGHT)
    {
        mlx_pixel_put(mlx, win, WIDTH / 2, i, 0x0000FF00);
        i++;
    }
}

void put_pixel(int x, int y, int color)
{
    x = WIDTH / 2 + x - (img_width * scale_factor) / 2;
    y = HEIGHT / 2 - y + (img_height * scale_factor) / 2;
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        insert_pixel(x, y, color);
}

int get_pixel_from_image(char *data, int width, int height, int x, int y, int line_size, int bpp)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        char *pixel = data + (y * line_size + x * (bpp / 8));
        return *(int *)pixel;
    }
    return 0;
}

void scale_image()
{
    scaled_img_width = (int)(img_width * scale_factor / res_downgrade);
    scaled_img_height = (int)(img_height * scale_factor / res_downgrade);

    if (scaled_img)
        mlx_destroy_image(mlx, scaled_img);

    scaled_img = mlx_new_image(mlx, scaled_img_width, scaled_img_height);
    scaled_data_addr = mlx_get_data_addr(scaled_img, &scaled_bpp, &scaled_size_line, &scaled_endian);

    int x, y;
    for (y = 0; y < scaled_img_height; y++)
    {
        for (x = 0; x < scaled_img_width; x++)
        {
            int orig_x = (int)(x * res_downgrade / scale_factor);
            int orig_y = (int)(y * res_downgrade / scale_factor);

            if (orig_x >= 0 && orig_x < img_width && orig_y >= 0 && orig_y < img_height)
            {
                int color = get_pixel_from_image(data_addr, img_width, img_height, orig_x, orig_y, size_line, bpp);
                char *pixel = scaled_data_addr + (y * scaled_size_line + x * (scaled_bpp / 8));
                *(int *)pixel = color;
            }
        }
    }
}

void rotate_image()
{
    // Implement the rotation logic here if needed
}

void interpolate_pixels()
{
    t_render *r = render(NULL);

    r->img_ptr = mlx_new_image(mlx, WIDTH, HEIGHT);
    r->img_data = mlx_get_data_addr(r->img_ptr, &r->bits_per_pixel, &r->size_line, &r->endian);

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            int src_x = (x - (WIDTH / 2 - (scaled_img_width * res_downgrade) / 2)) / res_downgrade;
            int src_y = ((HEIGHT / 2 + (scaled_img_height * res_downgrade) / 2) - y) / res_downgrade;

            if (src_x >= 0 && src_x < scaled_img_width && src_y >= 0 && src_y < scaled_img_height)
            {
                int color = get_pixel_from_image(scaled_data_addr, scaled_img_width, scaled_img_height, (int)src_x, (int)src_y, scaled_size_line, scaled_bpp);
                insert_pixel(x, y, color);
            }
        }
    }
}

int render_next_frame(void *ren)
{
    if (angle > 2 * M_PI)
        angle = 0;

    // usleep(16666);

    t_render *r = render(NULL);
    
    // Scale the image
    scale_image();
    rotate_image();

    // Interpolate and render the image
    interpolate_pixels();

    // Display the rendered image
    mlx_put_image_to_window(mlx, win, r->img_ptr, 0, 0);

    // Clean up
    mlx_destroy_image(mlx, r->img_ptr);

    if (scale_factor > 5)
        exit(0);
        // go_up = false;

    if (scale_factor < 0.5)
        go_up = true;

    if (go_up)
        scale_factor += 0.05;
    else
        scale_factor -= 0.05;

    angle += 0.05;
    return 0;
}

int main(int nb, char **arg)
{
    t_render *r = malloc(sizeof(t_render));
    render(r);

    printf("Resolution downgrade: %d\n", res_downgrade);
    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "3D Rotation");
    img = load_image();
    mlx_hook(win, KeyPress, KeyPressMask, exit, NULL);
    mlx_loop_hook(mlx, render_next_frame, NULL);
    mlx_loop(mlx);
}
