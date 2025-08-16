/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quality.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 00:20:23 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 20:15:45 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_quality(t_render *r)
{
	int	quality;

	pthread_mutex_lock(&r->quality_mutex);
	quality = r->quaility;
	pthread_mutex_unlock(&r->quality_mutex);
	return (quality);
}

void	update_quality(t_render *r, int quality)
{
	pthread_mutex_lock(&r->quality_mutex);
	r->quaility = quality;
	pthread_mutex_unlock(&r->quality_mutex);
}
