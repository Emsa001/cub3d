/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:57:03 by escura            #+#    #+#             */
/*   Updated: 2024/06/19 16:39:10 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_player()
{
    move_player();
	draw_player();

	float angle = player()->angle;

	player()->angle -= 0.01 * player()->fov;
	for(int i = 0; i < player()->fov * 2; i++){
		draw_line();
		player()->angle += 0.01;
	}
	player()->angle = angle;
}