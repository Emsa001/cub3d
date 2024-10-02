/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:53:45 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/02 15:08:35 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_block_id(t_block *blocks, float px, float py, float angle)
{
	int		i;
	float	x;
	float	y;
	float	p_x;
	float	p_y;
	float	full_angle;
	float	md;

	i = 0;
	x = 0;
	y = 0;
	p_x = px - 0.5 + 2.5 * cos(angle);
	p_y = py - 0.5 + 2.5 * sin(angle);
	full_angle = angle * 180 / PI;
	md = 2 + (-cos(angle * PI / 45));
	while (blocks[i].x != -1)
	{
		x = blocks[i].x;
		y = blocks[i].y;
		if ((p_x - md <= x && x <= p_x + md) && (p_y - md <= y && y <= p_y
				+ md))
			return (i);
		i++;
	}
	return (-1);
}

void	catch_block(float angle)
{
	t_player	*p;
	t_cube		*c;
	static int	id;

	p = player();
	c = cube();
	if (!c->map->blocks)
		return ;
	if (!p->catched)
	{
		id = get_block_id(c->map->blocks, p->x, p->y, angle);
		p->catched = true;
	}
	if (id == -1)
	{
		p->catched = false;
		return ;
	}
	c->map->blocks[id].x = p->x - 0.5 + 2.5 * cos(angle);
	c->map->blocks[id].y = p->y - 0.5 + 2.5 * sin(angle);
}
