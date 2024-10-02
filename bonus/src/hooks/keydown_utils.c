/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:44:54 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 22:24:59 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	handle_pause_controlls(int keycode, t_player *p, t_cube *c)
{
	if (keycode == ESC && p->gui != MATH)
	{
		if (p->gui != NONE && p->gui != PAUSE)
		{
			p->gui = NONE;
			return (false);
		}
		p->gui = NONE;
		if (is_paused())
			set_paused(false);
		else
		{
			p->gui = PAUSE;
			set_paused(true);
		}
	}
	return (false);
}

bool	handle_gui_controlls(int keycode, t_player *p)
{
	if (keycode == G)
	{
		if (p->gui == MATH)
			return (true);
		if (p->gui_temp != NONE && p->gui == NONE)
			p->gui = p->gui_temp;
		else
			p->gui = NONE;
	}
	if (keycode == E)
	{
		if (p->gui == MATH)
			return (true);
		if (p->gui == NONE)
			p->gui = INVENTORY;
		else
			p->gui = NONE;
	}
	return (false);
}

void	stop_slide(void)
{
	t_player	*p;

	p = player();
	p->slide = false;
}
