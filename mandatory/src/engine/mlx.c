/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:35:04 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 14:23:48 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	*load_image(char *path)
{
	const t_cube	*c = cube();
	void			*img;
	int				img_width;
	int				img_height;

	img = mlx_xpm_file_to_image(c->mlx, path, &img_width, &img_height);
	if (img == NULL)
		printf("Error: failed to load image: %s\n", path);
	return (img);
}

void	draw_image(void *img, int x, int y)
{
	const t_cube	*c = cube();

	mlx_put_image_to_window(c->mlx, c->win, img, x, y);
}

void	destroy_image(void *img)
{
	const t_cube	*c = cube();

	mlx_destroy_image(c->mlx, img);
}

void	clean_window(void)
{
	const t_cube	*c = cube();

	mlx_clear_window(c->mlx, c->win);
}

void	put_pixel(int x, int y, int color)
{
	t_render	*r;
	int			index;

	r = render();
	r->data = mlx_get_data_addr(r->img_ptr, &r->bpp, &r->size_line, &r->endian);
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * r->size_line + x * r->bpp / 8;
	r->data[index] = color & 0xFF;
	r->data[index + 1] = (color >> 8) & 0xFF;
	r->data[index + 2] = (color >> 16) & 0xFF;
}
