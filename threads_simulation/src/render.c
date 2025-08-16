#include "./simulation.h"

void	create_image(t_render *r, int width, int height)
{
	r->img_ptr = mlx_new_image(r->mlx, width, height);
	r->data = mlx_get_data_addr(r->img_ptr, &r->bpp, &r->size_line, &r->endian);
}

t_render	*init_render(t_render *r, char *title)
{
	static t_render	*render = NULL;

	if (r == NULL)
		return (render);
	r->mlx = mlx_init();
	r->win = mlx_new_window(r->mlx, WIDTH, HEIGHT, title);
	create_image(r, WIDTH, HEIGHT);
	render = r;
	return (render);
}

t_render *render()
{
    return init_render(NULL, NULL);
}

void put_pixel(int x, int y, int color, t_render *r)
{
	int index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0 || r->img_ptr == NULL)
		return;
	index = y * r->size_line + x * r->bpp / 8;
	r->data[index] = color & 0xFF;
	r->data[index + 1] = (color >> 8) & 0xFF;
	r->data[index + 2] = (color >> 16) & 0xFF;
}