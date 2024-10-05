/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:16:56 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 13:49:58 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_minimap(void)
{
	t_minimap	*m;
	t_map		*map;
	t_player	*p;

	m = minimap();
	map = cube()->map;
	p = player();
	draw_minimap_square(m->x, m->y);
	draw_player(m->center_x, m->center_y);
	draw_blocks(m, map, p);
}
