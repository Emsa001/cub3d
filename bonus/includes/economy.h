/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   economy.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:18:44 by escura            #+#    #+#             */
/*   Updated: 2024/09/20 12:40:35 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECONOMY_H
# define ECONOMY_H

# include "cub3d.h"

typedef struct s_async t_async;

typedef struct s_generator
{
	int 	id;
	int		x;
	int		y;
	
	int generated;
	int energy;
	int add_money;
	
	int speed;
	int level;

	int loop;

	pthread_mutex_t	mutex;
	struct s_generator	*next;
}			t_generator;

typedef struct s_store
{
	int		x;
	int		y;

	bool	case_cooldown;
	int		items[27];
	t_generator		*generators;

	pthread_mutex_t	case_mutex;

}			t_store;


void economy_loop();

void		shop_item_hover(void *arg);
void		cases(int x, int y);
void		special_offer(int x, int y);
void		shopkeeper(void);
void		portal_offer(int x, int y);

void generators();
void generator_gui();
t_generator *get_generator(int x, int y);
int gen_total_amount();
void generator_generating(t_async *current);

#endif
