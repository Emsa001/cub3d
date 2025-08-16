#include "simulation.h"

int render_scene_multithread(void)
{
	t_render *r = render();
	pthread_t thread;

	mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, 0, 0);
	pthread_create(&thread, NULL, start_threads, (void *)r);
	pthread_detach(thread);

	return 0;
}

int main(int argc, char **argv)
{
    int threads = 1;
    if(argc == 2)
        threads = atoi(argv[1]);

    char title[50];
    sprintf(title, "Simulation with %d threads", threads);

    t_render *r = init_render((t_render *)malloc(sizeof(t_render)), title);
    r->threads = threads;

    printf("Running simulation with %d threads\n", r->threads);

    mlx_loop_hook(r->mlx, render_scene_multithread, NULL);
    mlx_loop(r->mlx);

    return 0;
}