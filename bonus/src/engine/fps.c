/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:24:07 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 17:00:51 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

static double	get_time_seconds(void)
{
	struct timespec	ts;

	if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
	{
		printf("TIME ERROR clock_gettime\n");
		return (0.0);
	}
	return (ts.tv_sec + ts.tv_nsec / 1e9);
}

void	update_fps(void)
{
	const double	current_time = get_time_seconds();
	char			*fps_str;
	t_render *const	r = render();

	cube()->delta_time = current_time - r->last_time;
	r->last_time = current_time;
	r->frame_count++;
	if (current_time - r->fps_update_time >= 1.0)
	{
		r->fps = r->frame_count / (current_time - r->fps_update_time);
		r->fps_update_time = current_time;
		r->frame_count = 0;
	}
	if((int)r->fps <= 0)
		r->fps = 0;
	fps_str = ft_itoa((int)r->fps);
	put_string(fps_str, WIDTH - 60, 30, 0xFFFFFF);
	ft_free(fps_str);
}
