/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:32:21 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 20:16:03 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_thread_color(int i)
{
	const int	colors[12] = {
		0xFF0000,
		0x00FF00,
		0x0000FF,
		0xFFFF00,
		0xFF00FF,
		0x00FFFF,
		0xFFA500,
		0x800080,
		0x008000,
		0x000080,
		0x800000,
		0x808080,
	};

	return (colors[i % 12]);
}

static void	*draw_lines_thread(void *arg)
{
	t_thread_params *const	params = (t_thread_params *)arg;
	t_draw					draw;
	int						i;
	float					fraction;
	const int quality = get_quality(params->render);

	draw = init_draw();
	i = params->start;
	while (i < params->end)
	{
		fraction = (float)i / WIDTH;
		draw.angle = params->angle_offset + fraction * params->fov_in_radians;
		draw.start_x = i;
		draw_line(draw, params);
		i = i + quality;
	}
	free(draw.sprites);
	free(draw.facing);
	return (NULL);
}

void	render_view(t_cube *c)
{
	t_thread_params	params[NUM_THREADS];
	int				i;

	i = 0;
	while (i < NUM_THREADS)
	{
		params[i].start = i * WIDTH / NUM_THREADS;
		params[i].end = (i + 1) * WIDTH / NUM_THREADS;
		if (i + 1 == NUM_THREADS)
			params[i].end = WIDTH;
		params[i].fov_in_radians = player()->fov * PI / 180;
		params[i].angle_offset = player()->angle - (params[i].fov_in_radians
				/ 2.0);
		params[i].cube = c;
		params[i].render = render();
		params[i].player = player();
		params[i].textures = textures();
		params[i].color = get_thread_color(i);
		pthread_create(&params[i].thread_id, NULL, draw_lines_thread,
			&params[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
		pthread_join(params[i++].thread_id, NULL);
}
