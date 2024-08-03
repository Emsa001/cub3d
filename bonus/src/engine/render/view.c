/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:32:21 by escura            #+#    #+#             */
/*   Updated: 2024/08/03 18:34:22 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <pthread.h>
#define NUM_THREADS 2

void* draw_lines_thread(void* arg)
{
    ThreadParams *params = (ThreadParams*)arg;
    
    for (int i = params->start; i < params->end; i++) {
        float fraction = (float)i / WIDTH;
        float rayAngle = params->angleOffset + fraction * params->fovInRadians;
        
        draw_line(rayAngle, i, params);
    }
    return NULL;
}

void render_view()
{
    t_cube *c = cube();
    t_render *r = render();
    t_player *p = player();
    t_textures *t = textures();
    
    float angle = p->angle;
    float fovInRadians = p->fov * PI / 180;
    float halfFovInRadians = fovInRadians / 2.0;
    float angleOffset = angle - halfFovInRadians;

    pthread_t threads[NUM_THREADS];
    ThreadParams threadParams[NUM_THREADS];
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

    for (int i = 0; i < NUM_THREADS; i++) {
        threadParams[i].start = i * linesPerThread;
        threadParams[i].end = (i + 1 == NUM_THREADS) ? WIDTH : (i + 1) * linesPerThread;
        threadParams[i].angleOffset = angleOffset;
        threadParams[i].fovInRadians = fovInRadians;

        threadParams[i].cube = c;
        threadParams[i].render = r;
        threadParams[i].player = p;
        threadParams[i].textures = t;

        threadParams[i].color = colors[i];

        threadParams[i].mutex = &mutex;
        
        pthread_create(&threads[i], NULL, draw_lines_thread, &threadParams[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    mlx_put_image_to_window(r->mlx, r->win, r->img_ptr, 0, 0);
    mlx_destroy_image(r->mlx, r->img_ptr);
}
