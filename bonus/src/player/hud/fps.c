/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:24:07 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 16:12:22 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void update_fps(void) 
{
    static int fps = 0;
    static int last_fps = 0;
    static time_t last_time = 0;
    const t_render *r = render();
    
    time_t now = time(NULL);
    fps++;
    if (now - last_time >= 1) 
    {
        last_time = now;
        last_fps = fps;
        fps = 0;
    }
    
    char *fps_str = ft_itoa(last_fps);
    mlx_string_put(r->mlx, r->win, 10, 10, 0xFFFFFF, fps_str);
    ft_free(fps_str);
}
