/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:46:56 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 11:52:59 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_movement_con(t_player *p, bool is_moving, int speed)
{
	float	left_angle;
	float	right_angle;

	if (p->btn_a)
	{
		left_angle = p->angle - PI / 2;
		try_move(0, speed * sin(left_angle));
		try_move(speed * cos(left_angle), 0);
		is_moving = true;
	}
	if (p->btn_d)
	{
		right_angle = p->angle + PI / 2;
		try_move(0, speed * sin(right_angle));
		try_move(speed * cos(right_angle), 0);
		is_moving = true;
	}
	handle_step_animation(p, is_moving);
}

static void	handle_movement(t_player *p, int speed)
{
	float	cos_angle;
	float	sin_angle;
	bool	is_moving;

	cos_angle = cos(p->angle);
	sin_angle = sin(p->angle);
	is_moving = false;
	speed = p->speed;
	if (p->sprint)
		speed += SPRINTBONUS;
	sliding(p, &speed);
	if (p->btn_w || p->btn_s)
	{
		if (p->btn_s)
		{
			cos_angle = -cos_angle;
			sin_angle = -sin_angle;
		}
		try_move(0, speed * sin_angle);
		try_move(speed * cos_angle, 0);
		is_moving = true;
	}
	else
		p->sprint = false;
	handle_movement_con(p, is_moving, speed);
}

void	handle_interactions(t_player *p)
{
	if (p->interact)
	{
		if (p->opened)
			move_door(cube()->map, p, false);
		else
			move_door(cube()->map, p, true);
	}
	if (p->spawn)
	{
		add_block(p->angle);
		p->spawn = false;
	}
	if (p->remove && !p->catched)
	{
		remove_block(p->angle);
		p->remove = false;
	}
	if (p->catch)
		catch_block(p->angle);
}

void	handle_jumping(t_player *p)
{
	t_cube		*c;
	const float	base_z = 0.5;

	c = cube();
	if (p->jump_speed > 0)
	{
		p->z += p->jump_speed * c->delta_time;
		p->jump_speed -= GRAVITY * c->delta_time;
		if (p->slide)
		{
			p->slide = false;
		}
	}
	else if (p->jump_speed < 0)
	{
		p->fall_speed += GRAVITY * c->delta_time;
		p->z -= p->fall_speed * c->delta_time;
		if (p->z <= base_z)
		{
			p->z = base_z;
			p->jump_speed = 0;
			p->fall_speed = 0;
		}
	}
}

void	move_player(void)
{
	t_player	*p;
	int			speed;

	speed = 0;
	p = player();
	if (p->jumping == true && p->z <= 0.6)
	{
		p->jump_speed = JUMP_SPEED;
		p->fall_speed = 0;
	}
	handle_movement(p, speed);
	handle_arrow_rotation(p);
	handle_vertical_movement(p);
	handle_interactions(p);
	handle_jumping(p);
	update_player_position(p);
	update_player_direction(p);
}
