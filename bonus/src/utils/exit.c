/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:52:35 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 00:09:44 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

static void	clean_image(t_render *r)
{
	mlx_destroy_image(r->mlx, r->img_ptr);
	r->img_ptr = NULL;
}

void	destroy_sprite_image(t_sprite sprite)
{
	int	i;

	i = 0;
	while (i < sprite.frames)
	{
		destroy_texture(sprite.sprite_tex[i]);
		sprite.sprite_tex[i] = NULL;
		i++;
	}
}

void	destroy_render(void)
{
	t_render	*r;

	r = render();
	clean_image(r);
	mlx_destroy_window(r->mlx, r->win);
	mlx_destroy_display(r->mlx);
	free(r->mlx);
	pthread_mutex_destroy(&r->image_queue_mutex);
	pthread_mutex_destroy(&r->string_queue_mutex);
}

void	exit_game(int code)
{
	t_render	*r;
	t_sprite	*sprites;
	int			i;

	r = render();
	sprites = cube()->map->sprites;
	i = 0;
	destroy_manager();
	while (sprites[i].x != -1)
	{
		if (sprites[i].sprite_tex != NULL)
			destroy_sprite_image(sprites[i]);
		i++;
	}
	clear_image_queue(r);
	clear_string_queue(r);
	destroy_textures();
	destroy_render();
	ft_destructor();
	exit(code);
}
