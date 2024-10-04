/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 21:49:58 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	move_mouse_to_center(void)
// {
// 	const t_render	*r = render();

// 	mlx_mouse_move(r->mlx, r->win, WIDTH / 2, HEIGHT / 2);
// }

int	mouse_click(int button)
{
	t_player		*p;
	const t_render	*r = render();
	int				x;
	int				y;

	p = player();
	if(!cube()->accept_hooks)
		return (0);
	if (p->mouse_hook)
	{
		if (button == LEFT_CLICK)
		{
			if (p->hand != NULL)
				p->swing = true;
		}
		if (button == RIGHT_CLICK)
		{
			if (p->hand && p->hand->right_click != NULL)
				p->hand->right_click(p->hand);
		}
	}
	mlx_mouse_get_pos(r->mlx, r->win, &x, &y);
	button_click(button, x, y);
	return (0);
}

int	mouse_move(int x, int y)
{
	t_render	*r;

	r = render();
	if(!cube()->accept_hooks)
		return (0);
	r->mouse_x = x;
	r->mouse_y = y;
	ft_free(player()->hover);
	player()->hover = NULL;
	if (!player()->mouse_hook)
	{
		button_hover(x, y);
		return (0);
	}
	if (!cube()->paused)
		handle_mouse_rotate(x, y);
	return (0);
}
