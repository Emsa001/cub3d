/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:52:35 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 19:56:14 by escura           ###   ########.fr       */
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
	t_render *const	r = render();

	destroy_manager();
	destroy_sprites();
	clear_image_queue(r);
	clear_string_queue(r);
	destroy_textures();
	destroy_render();
	ft_destructor();
	exit(code);
}
