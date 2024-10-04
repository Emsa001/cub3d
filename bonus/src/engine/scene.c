/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:15:01 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 22:07:39 by escura           ###   ########.fr       */
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
	static int frame = 0;
	
	if(!render()->loading)
	{
		player()->mouse_hook = true;
		render_view(cube());
		render_player();
	}else
	{
		ft_bzero(render()->data, WIDTH * HEIGHT * 4);
		put_image(&textures()->ui->loading[frame / 7], 0, 80, 2.5);
		frame++;
		if(frame == 56)
			frame = 0;
	}
	execute_button_hover();
	render_queue();
	update_fps();
	show_image(0, 0);
	return (0);
}
