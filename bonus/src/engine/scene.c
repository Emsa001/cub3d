/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:15:01 by escura            #+#    #+#             */
/*   Updated: 2024/10/07 13:16:43 by btvildia         ###   ########.fr       */
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
	const t_render	*r = render();

	mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, x, y);
}

static void	render_queue(void)
{
	const t_render	*r = render();

	put_image_queue(r);
	put_string_queue(r);
	async_queue();
}

static void	render_scene_loading(void)
{
	static int	frame = 0;
	static int	buttons = 0;

	ft_bzero(render()->data, WIDTH * HEIGHT * 4);
	put_image(&textures()->ui->loading[frame / 4], 0, 80, 2.5);
	frame++;
	if (frame == 8 * 4)
		frame = 0;
	if (cube()->accept_hooks)
	{
		loading_exit();
		map_buttons(buttons / 5);
		if (buttons < 25)
			buttons++;
	}
	render_queue();
	show_image(0, 0);
}

int	render_scene_multithread(void)
{
	if (render()->loading)
	{
		render_scene_loading();
		return (0);
	}
	player()->mouse_hook = true;
	render_view(cube());
	render_player();
	execute_button_hover();
	render_queue();
	update_fps();
	show_image(0, 0);
	return (0);
}
