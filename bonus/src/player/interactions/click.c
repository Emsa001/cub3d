/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:04:34 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 13:55:33 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_mouseclick(int button)
{
	t_player		*p;
	t_cube			*c;
	const t_render	*r = render();

	p = player();
	c = cube();
	if (p->mouse_hook)
	{
		if (button == LEFT_CLICK)
		{
			if (p->hand != NULL)
				p->swing = true;
			p->catch = true;
		}
		if (button == RIGHT_CLICK)
		{
			if (p->hand->right_click != NULL){
				p->hand->right_click(p->hand);
			}
			p->catch = false;
			p->catched = false;
		}
	}
	int x, y;
	mlx_mouse_get_pos(r->mlx, r->win, &x, &y);
	button_click(button, x, y);
}
