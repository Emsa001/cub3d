/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_selector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 17:54:12 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 17:57:33 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	select_map(void *arg)
{
	cube()->selected_map = (intptr_t)arg;
}

static void	render_button_string(t_button button, int i)
{
	const int	colors[] = {0x67e8f9, 0x7dd3fc, 0x93c5fd, 0xa5b4fc, 0xc4b5fd};
	t_string	string;

	string = (t_string){0};
	string.str = ft_itoa(i + 1);
	string.color = colors[i];
	string.size = 1.5;
	string.x = button.x + 45;
	string.y = button.y + 40;
	render_string(&string);
	ft_free(string.str);
}

void	map_buttons(int buttons)
{
	t_button	button;
	const int	selected = cube()->selected_map;
	int			i;

	i = 0;
	while (i < buttons)
	{
		button = (t_button){0};
		button.x = WIDTH / 2 - 330 + i * 130;
		button.y = 150;
		button.size = 1.5;
		button.left_click = &select_map;
		button.selected = i == selected;
		button.arg = (void *)(intptr_t)i;
		button.is_default = true;
		add_button(&button);
		render_button_string(button, i);
		i++;
	}
}
