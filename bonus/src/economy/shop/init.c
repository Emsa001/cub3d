/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:07:56 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 20:39:43 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_store	*init_store(void)
{
	t_store		*store;
	const int	items[27] = {33, 279, 325, 273, 275, 282, 24, 168, 169, 170,
		171, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
	const int	prices[27] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
		1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000, 2100,
		2200, 2300, 2400, 2500, 2600, 2700};
	int			i;

	store = ft_calloc(1, sizeof(t_store));
	store->case_cooldown = false;
	pthread_mutex_init(&store->case_mutex, NULL);
	i = 0;
	while (i < 27)
	{
		store->items[i] = items[i];
		store->prices[i] = prices[i];
		i++;
	}
	store->generators = NULL;
	store->math[0] = 75;
	store->math[1] = 76;
	return (store);
}
