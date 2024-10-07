/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:53:45 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/07 15:06:35 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_block_id(t_block *blocks, float px, float py, float angle)
{
	int		i;
	t_float	point;
	t_float	point_p;
	float	full_angle;
	float	md;

	point.x = 0;
	point.y = 0;
	point_p.x = px - 0.5 + 1.5 * cos(angle);
	point_p.y = py - 0.5 + 1.5 * sin(angle);
	i = 0;
	full_angle = angle * 180 / PI;
	md = 2 + (-cos(angle * PI / 45));
	while (blocks[i].x != -1)
	{
		point.x = blocks[i].x;
		point.y = blocks[i].y;
		if ((point_p.x - md <= point.x && point.x <= point_p.x + md)
			&& (point_p.y - md <= point.y && point.y <= point_p.y + md))
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
