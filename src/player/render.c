/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:57:03 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 20:43:05 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_player(void)
{
	t_cube		*c;
	t_player	*p;
	float		angle;
	int			multipler;

	move_player();
	draw_player();
	c = cube();
	p = player();
	angle = p->angle;
	multipler = 4;
	c->x = 0;
	p->angle -= 0.01 / (multipler / 2) * p->fov * (multipler / 2);
	for (int i = 0; i < p->fov * multipler; i++)
	{
		draw_line();
		p->angle += 0.01 / (multipler / 2);
		c->x += WIDTH / (p->fov * multipler);
	}
	p->angle = angle;
}
