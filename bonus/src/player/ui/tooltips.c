/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tooltips.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:41:37 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 02:29:41 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	tooltip(char *string, float size)
{
	const t_render	*r = render();
	t_string		str;

	put_image(textures()->tooltip_bg, r->mouse_x - 10, r->mouse_y - 40, 3);
	str = (t_string){0};
	str.str = string;
	str.color = 0xFFFFFF;
	str.size = size;
	str.x = r->mouse_x + size * 20;
	str.y = r->mouse_y - (size) * 50;
	render_string(&str);
}

void	render_tooltip(void)
{
	t_player	*p;
	t_button	*button;

	p = player();
	if (p->hover != NULL)
	{
		button = p->hover;
		if (button->hover != NULL)
			((void (*)(void *))button->hover)(button->arg);
	}
}
