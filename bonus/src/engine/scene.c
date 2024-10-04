/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:15:01 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 19:44:11 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_image(t_render *r, int width, int height)
{
	r->img_ptr = mlx_new_image(r->mlx, width, height);
	r->data = mlx_get_data_addr(r->img_ptr, &r->bpp, &r->size_line, &r->endian);
}

static void	show_image(int x, int y)
{
	t_render *const	r = render();

	mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, x, y);
}

static void	render_queue(void)
{
	t_render *const	r = render();

	put_image_queue(r);
	put_string_queue(r);
	async_queue();
}

int	render_scene_multithread(void)
{
	player()->mouse_hook = true;
	render_view(cube());
	render_player();
	execute_button_hover();
	render_queue();
	update_fps();
	show_image(0, 0);

	return (0);
}
