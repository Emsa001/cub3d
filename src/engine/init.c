/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 20:45:29 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* CUBE */

t_cube	*init_cube(t_cube *c)
{
	static t_cube	*cube;
	
	if (c == NULL)
		return (cube);

	c->mlx = mlx_init();
	c->keycode = D;
	
	t_render *r = ft_malloc(sizeof(t_render));
	r->mlx = c->mlx;
	init_render(r);


	t_textures *t = ft_malloc(sizeof(t_textures));
	t_texture *sky = ft_malloc(sizeof(t_texture));
	t_texture *floor = ft_malloc(sizeof(t_texture));
	t_texture *wall = ft_malloc(sizeof(t_texture));

	sky->image = mlx_xpm_file_to_image(c->mlx, "assets/sky.xpm", &sky->width, &sky->height);
	sky->img_data = mlx_get_data_addr(sky->image, &sky->bpp, &sky->size_line, &sky->endian);
	t->sky = sky;

	floor->image = mlx_xpm_file_to_image(c->mlx, "assets/floor.xpm", &floor->width, &floor->height);
	floor->img_data = mlx_get_data_addr(floor->image, &floor->bpp, &floor->size_line, &floor->endian);
	t->floor = floor;

	wall->image = mlx_xpm_file_to_image(c->mlx, "assets/wall.xpm", &wall->width, &wall->height);
	wall->img_data = mlx_get_data_addr(wall->image, &wall->bpp, &wall->size_line, &wall->endian);
	t->wall = wall;

	// init_textures(t);

	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (init_cube(NULL));
}

t_render *init_render(t_render *r)
{
	static t_render	*render;

	if (r == NULL)
		return (render);

	render = r;
	return (render);
}

t_render *render(void)
{
	return (init_render(NULL));
}

t_textures *init_textures(t_textures *t)
{
	static t_textures	*texture;

	if (t == NULL)
		return (texture);

	texture = t;
	return (texture);
}

t_textures *textures(void)
{
	return (init_textures(NULL));
}