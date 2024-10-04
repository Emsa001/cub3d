/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:21:03 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 20:44:31 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void	consume_end(void *arg)
{
	t_itemprops	*props;

	props = (t_itemprops *)arg;
	printf("Consumed %d for %d\n", props->id, props->effect);
	*(props->intvar) -= props->effect;
	player()->effects--;
	ft_free(props);
}

void	consume(t_itemprops props)
{
	const int	time = props.time;
	t_location	*l;
	t_itemprops	*props_ptr;

	if (player()->effects >= 3)
		return ;
	l = (t_location *)ft_calloc(sizeof(t_location), 1);
	props_ptr = (t_itemprops *)ft_malloc(sizeof(t_itemprops));
	ft_memcpy(props_ptr, &props, sizeof(t_itemprops));
	player()->effects++;
	*(props.intvar) += props.effect;
	l->x = WIDTH - (200 * player()->effects);
	l->y = 50;
	string_timer(time, l);
	ft_wait(time, &consume_end, (void *)(props_ptr));
	printf("Consuming %d\n", props.id);
	player()->inventory[props.playerslot] = -1;
}
