/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:04:34 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 20:17:03 by btvildia         ###   ########.fr       */
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
			if (p->hand && p->hand->right_click != NULL){
				p->hand->right_click(p->hand);
			}
		}
	}
	int x, y;
	mlx_mouse_get_pos(r->mlx, r->win, &x, &y);
	button_click(button, x, y);
}
