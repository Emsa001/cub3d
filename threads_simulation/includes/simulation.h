#ifndef SIMULATION_H
#define SIMULATION_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "mlx/mlx.h"

#define WIDTH 1200
#define HEIGHT 1200

typedef struct s_render
{
	void *mlx;
	void *win;
	void *img_ptr;
	char *data;

	int bpp;
	int size_line;
	int endian;

	int threads;
} t_render;

typedef struct s_thread_params
{
	int start;
	int end;
	float angle_offset;
	float fov_in_radians;

	int color;

	t_render *render;
	pthread_t thread_id;
} t_thread_params;

t_render	*init_render(t_render *r, char *title);
t_render *render();
void put_pixel(int x, int y, int color, t_render *r);

void *start_threads(void *ren);
int get_thread_color(int i);


#endif