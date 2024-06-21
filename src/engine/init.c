/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:10:09 by escura            #+#    #+#             */
/*   Updated: 2024/06/21 12:55:10 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*init_texture(t_cube *c)
{
	t_texture	*texture;

	texture = ft_malloc(sizeof(t_texture));
	texture->img = mlx_xpm_file_to_image(c->mlx, "assets/1.xpm",
			&texture->width, &texture->height);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
	texture->width = 64;
	texture->height = 64;
	return (texture);
}

/* CUBE */

t_cube	*init_cube(t_cube *c)
{
	static t_cube	*cube;

	if (c == NULL)
		return (cube);
	c->mlx = mlx_init();
	c->keycode = D;
	c->texture = init_texture(c);
	cube = c;
	return (cube);
}

t_cube	*cube(void)
{
	return (init_cube(NULL));
}
