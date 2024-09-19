/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:35:04 by escura            #+#    #+#             */
/*   Updated: 2024/09/15 15:08:51 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void *load_image(char *path)
{
    const t_render *r = render();

    void	*img;
    int		img_width;
    int		img_height;

    img = mlx_xpm_file_to_image(r->mlx, path, &img_width, &img_height);
    if (img == NULL)
        printf("Error: failed to load image: %s\n", path);
    return img;
}

void draw_image(void *img, int x, int y)
{
    const t_render *r = render();

	mlx_put_image_to_window(r->mlx, r->win, img, x, y);
}


void destroy_image(void *img)
{
    const t_render *r = render();

    if (r != NULL && r->mlx != NULL && img != NULL)
    {
        mlx_destroy_image(r->mlx, img);
    }
}

void clean_window()
{
    const t_render *r = render();

    mlx_clear_window(r->mlx, r->win);
}

void put_pixel(int x, int y, int color, t_render *r)
{
    if(x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
        return ;

    // if(r->img_ptr == NULL)
    //     return ;

    int index = y * r->size_line + x * r->bpp / 8;
    
    r->data[index] = color & 0xFF;              // Blue component
    r->data[index + 1] = (color >> 8) & 0xFF;   // Green component
    r->data[index + 2] = (color >> 16) & 0xFF;  // Red component
}