/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:15:01 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 16:05:16 by escura           ###   ########.fr       */
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


static void select_map(void *arg){
	int map = (intptr_t)arg;

	cube()->selected_map = map;
	printf("Selected map: %d\n", map);
}

static void map_buttons()
{
	const int selected = cube()->selected_map;
	int i = 0;

	while(i < 5)
	{
		t_button button;
		button = (t_button){0};
		button.x = WIDTH / 2 - 330 + i * 130;
		button.y = 150;
		button.size = 1.5;
		button.left_click = &select_map;
		button.selected = i == selected;
		button.arg = (void *)(intptr_t)i;
		button.is_default = true;
		add_button(&button);
		i++;
	}
}

int	render_scene_multithread(void)
{
	static int frame = 0;
	
	int timing = 4;
	if(render()->loading)
	{
		ft_bzero(render()->data, WIDTH * HEIGHT * 4);
		put_image(&textures()->ui->loading[frame / timing], 0, 80, 2.5);
		frame++;
		if(frame == 8 * timing)
			frame = 0;
		map_buttons();
		render_queue();
		show_image(0, 0);
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
