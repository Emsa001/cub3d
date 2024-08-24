/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:24:07 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 14:05:04 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

static double last_time = 0.0;
static int frame_count = 0;
static double fps = 0.0;

double get_time_seconds() {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1) {
        perror("clock_gettime");
        return 0.0;
    }
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void update_fps(void) 
{
    const t_render *r = render();
    double current_time = get_time_seconds();
    frame_count++;

    // Update FPS every second (or other interval)
    if (current_time - last_time >= 1.0) {
        fps = frame_count / (current_time - last_time);
        if(current_time - last_time <= 5)
            cube()->delta_time = current_time - last_time;
        last_time = current_time;
        frame_count = 0;
    }
    
    char *fps_str = ft_itoa((int)fps);
    mlx_string_put(r->mlx, r->win, WIDTH - 50, 30, 0xFFFFFF, fps_str);
    ft_free(fps_str);
}
