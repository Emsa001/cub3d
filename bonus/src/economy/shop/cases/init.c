/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:27:50 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 18:21:44 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_cases(int x, int y)
{
	const int	values[3] = {1000, 10000, 50000};
	int			i;
	t_button	button;

	i = 0;
	while (i < 3)
	{
		button.x = x + 315 + (i % 3) * 140;
		button.y = y + 160 + (i / 3) * 140;
		button.width = 128;
		button.height = 128;
		button.function = &start_case;
		button.hover = &shop_item_hover;
		button.arg = (void *)(intptr_t)values[i];
		button.item_id = 71;
		add_button(&button);
		item_button(&button, 1.5);
		i++;
	}
}
