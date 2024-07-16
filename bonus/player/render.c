/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:57:03 by escura            #+#    #+#             */
/*   Updated: 2024/06/20 19:57:55 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(void)
{
	const t_cube	*c = cube();
	const t_player	*p = player();

	draw_cube(p->x_px, p->y_px, 5, 0x00FF0000);
}

void render_player(void) {
	t_cube *c = cube();
	t_player *p = player();

	move_player();
	// draw_player();
}