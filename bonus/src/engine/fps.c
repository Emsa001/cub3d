/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:24:07 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 15:38:30 by escura           ###   ########.fr       */
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

double fps_update_time = 0;

void update_fps(void) 
{
    const t_render *r = render();
    double current_time = get_time_seconds();
    
    // Calculate delta time per frame
    cube()->delta_time = current_time - last_time;
    last_time = current_time;

    frame_count++;

    // Update FPS every second (or other interval)
    if (current_time - fps_update_time >= 1.0) {
        fps = frame_count / (current_time - fps_update_time);
        fps_update_time = current_time;
        frame_count = 0;
    }

    // Convert FPS to string and render it on screen
    char *fps_str = ft_itoa((int)fps);

    t_string str = {0};
    str.str = fps_str;
    str.color = 0xFFFFFF;
    str.size = 0.5;
    str.x = WIDTH - 50;
    str.y = 30;

    render_string(&str);

    ft_free(fps_str);
}
