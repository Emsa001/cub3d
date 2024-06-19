/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:57:03 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 20:29:08 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_player()
{
    move_player();
	draw_player();
	t_cube *c = cube();
	t_player *p = player();

	float angle = p->angle;

	int multipler = 10;

	c->x = 0;

	p->angle -= 0.01/(multipler/2) * p->fov * (multipler /2);
	
	for(int i = 0; i < p->fov * multipler; i++){
		draw_line();
		p->angle += 0.01/(multipler/2);
		c->x += WIDTH / (p->fov * multipler);
	}
	
	p->angle = angle;
}