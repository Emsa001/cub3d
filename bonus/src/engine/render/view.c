/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:32:21 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 12:41:30 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*draw_lines_thread(void *arg)
{
	t_thread_params	*params;
	t_draw			draw;
	int				i;
	float			fraction;

	params = (t_thread_params *)arg;
	draw = init_draw();
	i = params->start;
	while (i < params->end)
	{
		fraction = (float)i / WIDTH;
		draw.angle = params->angle_offset + fraction * params->fov_in_radians;
		draw.start_x = i;
		draw_line(draw, params);
		i = i + WIDTH_SCALE;
	}
	free(draw.sprites);
	free(draw.facing);
	return (NULL);
}

void	render_view(t_cube *c)
{
	t_render *r = render();
	t_player *p = player();
	t_textures *t = textures();

	float angle = p->angle;
	float fov_in_radians = p->fov * PI / 180;
	float halfFovInRadians = fov_in_radians / 2.0;
	float angle_offset = angle - halfFovInRadians;

	pthread_t threads[NUM_THREADS];
	t_thread_params t_thread_params[NUM_THREADS];
	pthread_mutex_t mutex;

	int linesPerThread = WIDTH / NUM_THREADS;

	pthread_mutex_init(&mutex, NULL);

	int colors[12] = {
		0xFF0000, // red
		0x00FF00, // green
		0x0000FF, // blue
		0xFFFF00, // yellow
		0xFF00FF, // magenta
		0x00FFFF, // cyan
		0xFFA500, // orange
		0x800080, // purple
		0x008000, // dark green
		0x000080, // dark blue
		0x800000, // dark red
		0x808080, // gray
	};

	for (int i = 0; i < NUM_THREADS; i++)
	{
		t_thread_params[i].start = i * linesPerThread;
		t_thread_params[i].end = (i + 1 == NUM_THREADS) ? WIDTH : (i + 1) * linesPerThread;
		t_thread_params[i].angle_offset = angle_offset;
		t_thread_params[i].fov_in_radians = fov_in_radians;

		t_thread_params[i].cube = c;
		t_thread_params[i].render = r;
		t_thread_params[i].player = p;
		t_thread_params[i].textures = t;

		t_thread_params[i].color = colors[i % 12];

		t_thread_params[i].mutex = &mutex;

		pthread_create(&threads[i], NULL, draw_lines_thread, &t_thread_params[i]);
	}

	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutex); // Clean up the mutex when done
}