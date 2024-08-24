/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:08:59 by escura            #+#    #+#             */
/*   Updated: 2024/08/23 22:22:18 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void draw_cross_in_centre(t_render *r)
{
    int x_center = WIDTH / 2;
    int y_center = HEIGHT / 2;
    int i = -7;

	while (i <= 7)
	{
		put_pixel(x_center + i, y_center, 0x0000FF00, r);
		put_pixel(x_center, y_center + i, 0x0000FF00, r);
		i++;
	}
}


void render_player(){
    draw_cross_in_centre(render());
}