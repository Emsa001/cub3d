/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:39:43 by escura            #+#    #+#             */
/*   Updated: 2024/09/30 20:27:47 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_mouse_rotate(int x, int y)
{
	t_player	*p;
	int			dx;
	int			dy;

	p = player();
	dx = x - WIDTH / 2;
	dy = y - HEIGHT / 2;
	p->angle += dx * MOUSE_SENSITIVITY;
	if (p->z_dir > 1)
		p->z_dir = 1;
	if (p->z_dir < 0)
		p->z_dir = 0;
	if (p->angle > 2 * PI)
		p->angle -= 2 * PI;
	if (p->angle < 0)
		p->angle += 2 * PI;
}

void	handle_arrow_rotation(t_player *p)
{
	const double	delta_time = cube()->delta_time;

	if (p->btn_left)
	{
		p->angle -= 20 * MOUSE_SENSITIVITY * delta_time;
		if (p->angle < 0)
			p->angle += 2 * PI;
	}
	if (p->btn_right)
	{
		p->angle += 20 * MOUSE_SENSITIVITY * delta_time;
		if (p->angle > 2 * PI)
			p->angle -= 2 * PI;
	}
}
