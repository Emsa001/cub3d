#include "test.h"

void *mlx;
void *win;
void *img;
int img_width, img_height;
char *data_addr;
int bpp, size_line, endian;

float scale = 1;

typedef struct s_render {
    void *img_ptr;
    char *img_data;
    int bits_per_pixel;
    int size_line;
    int endian;
} t_render;

t_render *render(t_render *ren) {
    static t_render *r;
    if (ren) r = ren;
    return r;
}

void *load_image() {
    char *relative_path = "./assets/wall2.xpm";
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    if (!img) {
        printf("Error loading image\n");
        exit(1);
    }
    data_addr = mlx_get_data_addr(img, &bpp, &size_line, &endian);
    printf("Image loaded: width=%d, height=%d, bpp=%d, size_line=%d\n", img_width, img_height, bpp, size_line);
    return img;
}

void put_pixel(int x, int y, int color) {
    if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0) return;
    
    t_render *r = render(NULL);
    int index = y * r->size_line + x * r->bits_per_pixel / 8;
    
    r->img_data[index] = color & 0xFF;              // Blue component
    r->img_data[index + 1] = (color >> 8) & 0xFF;   // Green component
    r->img_data[index + 2] = (color >> 16) & 0xFF;  // Red component
}

int get_pixel_from_image(char *data, int width, int height, int x, int y, int line_size) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        char *pixel = data + (y * line_size + x * (bpp / 8));
        return *(int *)pixel;
    }
    return 0;
}

void draw_column(int x, int height, int offset, double scale_factor) {
    int y = 0;
    while (y < height * scale_factor) {
        int original_x = x / scale_factor;
        int original_y = y / scale_factor;
        int color = get_pixel_from_image(data_addr, img_width, img_height, original_x, original_y, size_line);
        put_pixel(x + offset, y, color);
        y++;
    }
}

void generate_image(int offset, float distance) {
    int width = img_width;
    int height = img_height;
    double scale_factor = 1.0;

    for (int x = 0; x < width * scale_factor; x++) {
        draw_column(x, height, offset, scale_factor);
    }
}

int render_next_frame(void *ren) {

    t_render *r = render(NULL);
    r->img_ptr = mlx_new_image(mlx, WIDTH, HEIGHT);
    r->img_data = mlx_get_data_addr(r->img_ptr, &r->bits_per_pixel, &r->size_line, &r->endian);
    
    generate_image(0, scale);

    mlx_put_image_to_window(mlx, win, r->img_ptr, 0, 0);
    mlx_destroy_image(mlx, r->img_ptr);

    return 0;
}

int main(int nb, char **arg) {
    t_render *r = malloc(sizeof(t_render));
    render(r);

    mlx = mlx_init();
    win = mlx_new_window(mlx, WIDTH, HEIGHT, "3D Rotation");
    img = load_image();

    mlx_loop_hook(mlx, render_next_frame, NULL);
    mlx_hook(win, KeyPress, KeyPressMask, kd, NULL);
    mlx_loop(mlx);
}
