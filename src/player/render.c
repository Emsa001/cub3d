/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:57:03 by escura            #+#    #+#             */
/*   Updated: 2024/06/21 15:29:38 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_player(void)
{
	const t_cube	*c = cube();
	const t_player	*p = player();

	draw_cube(p->x_px, p->y_px, 5, 0x00FF0000);
}

void	render_player(void)
{
	t_cube *c = cube();
	t_player *p = player();

	move_player();
	draw_player();

	float angle = p->angle;
	int numRays = 150; // Set numRays to a constant value
	int i = 0;

	float fovInRadians = p->fov * PI / 180;
	float halfFovInRadians = fovInRadians / 2.0;
	float angleOffset = angle - halfFovInRadians;

	float rayWidth = (float)WIDTH / numRays;

	while (i < numRays)
	{
		float fraction = (float)i / numRays;
		float rayAngle = angleOffset + fraction * fovInRadians;
		draw_line(rayAngle, i);
		c->x = rayWidth * i;
		c->y = HEIGHT / 2;
		i++;
	}
}