#include "simulation.h"

int get_thread_color(int i)
{
	const int colors[12] = {
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

static void draw_line(t_render *r, int color, int i)
{
	int x = 0;

	while (x < HEIGHT)
	{
		put_pixel(i, x, color, r);
		x++;
	}
	usleep(30000);
}

static void *draw_lines_thread(void *arg)
{
	t_thread_params *const params = (t_thread_params *)arg;
	t_render *const render = params->render;
	int i;

	i = params->start;
	while (i < params->end)
	{
		draw_line(render, params->color, i);
		i++;
	}
	return (NULL);
}

void *start_threads(void *ren)
{
	t_render *const r = (t_render *)ren;
	t_thread_params params[r->threads];
	int i;

	i = 0;
	while (i < r->threads)
	{
		params[i].start = i * WIDTH / r->threads;
		params[i].end = (i + 1) * WIDTH / r->threads;
		if (i + 1 == r->threads)
			params[i].end = WIDTH;
		params[i].render = r;
		params[i].color = get_thread_color(i);
		pthread_create(&params[i].thread_id, NULL, draw_lines_thread,
					   &params[i]);
		i++;
	}
	i = 0;
	while (i < r->threads)
		pthread_join(params[i++].thread_id, NULL);

	exit(0);
	return NULL;
}