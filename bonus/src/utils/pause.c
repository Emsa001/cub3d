/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:32:12 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 19:57:23 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_paused(void)
{
	t_cube	*c;

	c = cube();
	pthread_mutex_lock(&c->pause_mutex);
	if (c->paused)
	{
		pthread_mutex_unlock(&c->pause_mutex);
		return (true);
	}
	pthread_mutex_unlock(&c->pause_mutex);
	return (false);
}

void	set_paused(bool paused)
{
	t_cube	*c;

	c = cube();
	pthread_mutex_lock(&c->pause_mutex);
	c->paused = paused;
	pthread_mutex_unlock(&c->pause_mutex);
}
