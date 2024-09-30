/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:56:21 by escura            #+#    #+#             */
/*   Updated: 2024/09/28 14:08:44 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player_position(t_player *p)
{
	p->x = p->x_px / BLOCK_SIZE;
	p->y = p->y_px / BLOCK_SIZE;
}

void	update_player_direction(t_player *p)
{
	p->x_dir = cos(p->angle);
	p->y_dir = sin(p->angle);
	p->direction = p->angle * (180 / PI);
	if (p->direction > 180)
		p->direction -= 360;
}

void	handle_vertical_movement(t_player *p)
{
	if (p->btn_up)
		p->z += 0.1;
	if (p->btn_down)
		p->z -= 0.1;
}

void	handle_step_animation(t_player *p, bool is_moving)
{
	static float	step_progress = 0;
	const float		step_amplitude = 0.04;
	float			step_frequency;
	const float		base_z = 0.55;

	step_frequency = 0.2;
	if (p->sprint)
		step_frequency = 0.3;
	if (is_moving && p->jump_speed == 0)
	{
		step_progress += step_frequency;
		p->z = base_z + step_amplitude * sin(step_progress);
	}
	else if (p->jump_speed == 0)
		p->z = base_z;
}

void	try_move(float x, float y)
{
	const double	delta_time = cube()->delta_time;
	t_player		*p;
	int				temp_x;
	int				temp_y;

	p = player();
	temp_x = p->x_px;
	temp_y = p->y_px;
	p->x_px += x * delta_time;
	p->y_px += y * delta_time;
	if (touch())
	{
		p->x_px = temp_x;
		p->y_px = temp_y;
	}
}
