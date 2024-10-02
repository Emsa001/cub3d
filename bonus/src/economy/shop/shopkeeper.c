/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shopkeeper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:07:27 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 18:22:32 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	shopkeeper(void)
{
	t_location *const	find = is_nearby('M');
	t_player			*p;

	p = player();
	if (find)
	{
		p->gui_temp = STORE;
		interaction_notify("Press G to open a shop");
	}
	else if (p->gui_temp == STORE)
	{
		p->gui_temp = NONE;
		p->gui = NONE;
	}
	if (p->gui == STORE)
		open_store();
	ft_free(find);
}
