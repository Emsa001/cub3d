/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:35:04 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 20:43:32 by escura           ###   ########.fr       */
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
    t_render *r = render();

    r->img_data = mlx_get_data_addr(r->img_ptr, &r->bits_per_pixel, &r->size_line, &r->endian);
    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return ;
        
    r->img_data[y * r->size_line + x * r->bits_per_pixel / 8] = color;
}