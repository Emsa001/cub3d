/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:32:21 by escura            #+#    #+#             */
/*   Updated: 2024/09/10 17:58:24 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void* draw_lines_thread(void* arg)
{
    ThreadParams *params = (ThreadParams*)arg;
    t_draw draw = init_draw();
    
    for (int i = params->start; i < params->end; i++) {
        float fraction = (float)i / WIDTH;
        draw.angle = params->angleOffset + fraction * params->fovInRadians;
        draw.start_x = i;
        draw_line(draw, params);
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

        threadParams[i].color = colors[i % 12];

        threadParams[i].mutex = &mutex;
        
        pthread_create(&threads[i], NULL, draw_lines_thread, &threadParams[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);  // Clean up the mutex when done
}
