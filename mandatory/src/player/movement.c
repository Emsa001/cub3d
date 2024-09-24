/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:57:53 by escura            #+#    #+#             */
/*   Updated: 2024/09/23 14:09:31 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	try_move(float x, float y)
{
	const t_cube	*c = cube();
	t_player		*p;
	int				temp_x;
	int				temp_y;

	p = player();
	temp_x = p->x_px;
	temp_y = p->y_px;
	p->x_px += x;
	p->y_px += y;
	if (is_touching(p->x_px, p->y_px))
	{
		p->x_px -= x;
		p->y_px -= y;
	}
}

void	handle_forward_backward_movement(t_player *p, float cos_angle,
		float sin_angle)
{
	if (p->btn_w || p->btn_s)
	{
		if (p->btn_s)
		{
			cos_angle = -cos_angle;
			sin_angle = -sin_angle;
		}
		try_move(0, p->speed * sin_angle);
		try_move(p->speed * cos_angle, 0);
	}
}

void	handle_strafe_movement(t_player *p)
{
	float	left_angle;
	float	right_angle;

	if (p->btn_a)
	{
		left_angle = p->angle - PI / 2;
		try_move(0, p->speed * sin(left_angle));
		try_move(p->speed * cos(left_angle), 0);
	}
	if (p->btn_d)
	{
		right_angle = p->angle + PI / 2;
		try_move(0, p->speed * sin(right_angle));
		try_move(p->speed * cos(right_angle), 0);
	}
}

void	handle_rotation(t_player *p)
{
	if (p->btn_left)
	{
		p->angle -= 0.1;
		if (p->angle < 0)
			p->angle += 2 * PI;
	}
	if (p->btn_right)
	{
		p->angle += 0.1;
		if (p->angle > 2 * PI)
			p->angle -= 2 * PI;
	}
}

void	move_player(void)
{
	t_player	*p;
	float		cos_angle;
	float		sin_angle;

	p = player();
	cos_angle = cos(p->angle);
	sin_angle = sin(p->angle);
	handle_forward_backward_movement(p, cos_angle, sin_angle);
	handle_strafe_movement(p);
	handle_rotation(p);
	p->x = p->x_px / BLOCK_SIZE;
	p->y = p->y_px / BLOCK_SIZE;
	p->x_dir = cos(p->angle);
	p->y_dir = sin(p->angle);
	p->direction = p->angle * (180 / PI);
	if (p->direction > 180)
		p->direction -= 360;
}
