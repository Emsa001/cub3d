/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   economy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:18:44 by escura            #+#    #+#             */
/*   Updated: 2024/09/14 13:52:11 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECONOMY_H
# define ECONOMY_H

# include "cub3d.h"

typedef struct s_store
{
	int		x;
	int		y;

	bool	can_open;
	bool	open;
	bool	case_cooldown;
	int		items[27];
	int		cases[3];
	int		generators[2];

	pthread_mutex_t	case_mutex;

}			t_store;

void		shop_item_hover(void *arg);
void		cases(int x, int y);
void		special_offer(int x, int y);
void		shopkeeper(void);
void		portal_offer(int x, int y);

#endif
