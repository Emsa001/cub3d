/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:24:21 by escura            #+#    #+#             */
/*   Updated: 2024/10/07 18:02:58 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	generators(void)
{
	t_player			*p;
	t_location *const	find = is_nearby('G');

	p = player();
	if (find)
	{
		p->gui_temp = GENERATOR;
		p->generator = get_generator(find->x, find->y);
		interaction_notify("Press G to open a Generator");
	}
	else if (p->gui_temp == GENERATOR)
	{
		p->gui_temp = NONE;
		p->gui = NONE;
		printf("You left the generator\n");
	}
	ft_free(find);
	if (p->gui == GENERATOR)
		generator_gui();
}
