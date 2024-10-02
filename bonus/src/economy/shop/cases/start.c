/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:26:21 by escura            #+#    #+#             */
/*   Updated: 2024/10/01 16:33:18 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cooldown_end(t_async *async)
{
	t_store	*store;

	store = player()->store;
	pthread_mutex_lock(&store->case_mutex);
	store->case_cooldown = false;
	pthread_mutex_unlock(&store->case_mutex);
}

static void	start_cooldown(t_async *async)
{
	t_store	*store;

	store = player()->store;
	pthread_mutex_lock(&store->case_mutex);
	store->case_cooldown = true;
	pthread_mutex_unlock(&store->case_mutex);
}

static bool	cooldown(void)
{
	const t_store	*store = player()->store;
	t_async			*async;

	pthread_mutex_lock(&store->case_mutex);
	if (store->case_cooldown)
	{
		pthread_mutex_unlock(&store->case_mutex);
		tooltip("Cooldown", 1);
		return (true);
	}
	pthread_mutex_unlock(&store->case_mutex);
	async = new_async();
	async->process = &start_cooldown;
	async->end = &cooldown_end;
	async->time = 1500;
	start_async(async);
	return (false);
}

void	start_case(void *arg)
{
	t_player	*p;
	const int	value = (int)(intptr_t)arg;
	const int	prize = random_int(0, value * 2);
	t_texture	*prizeTexture;

	p = player();
	if (cooldown())
		return ;
	if(money() < value)
		return ;
	add_money(-value);
	p->GUI = NONE;
	displayPrizeMessage(prize, value);
	add_money(prize);
	prizeTexture = determinePrizeTexture(prize);
	renderPrizeImage(prizeTexture, 1000);
}
