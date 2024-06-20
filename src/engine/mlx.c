/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:35:04 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 14:43:50 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void *load_image(char *path)
{
    const t_cube *c = cube();

    void	*img;
    int		img_width;
    int		img_height;

    img = mlx_xpm_file_to_image(c->mlx, path, &img_width, &img_height);
    if (img == NULL)
        printf("Error: failed to load image: %s\n", path);
    return img;
}

void draw_image(void *img, int x, int y)
{
    const t_cube *c = cube();

	mlx_put_image_to_window(c->mlx, c->win, img, x, y);
}

void destroy_image(void *img)
{
    const t_cube *c = cube();

    mlx_destroy_image(c->mlx, img);
}

void clean_window()
{
    const t_cube *c = cube();

    mlx_clear_window(c->mlx, c->win);
}

void put_pixel(int x, int y, int color)
{
    const t_cube *c = cube();

    mlx_pixel_put(c->mlx, c->win, x, y, color);
}