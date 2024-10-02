/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:37:10 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 16:32:45 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	generator_add_money(t_generator *gen)
{
	const int	add = random_int(10, 100000 * gen->random);
	char		*addstr;
	t_string	extra;

	add_money(add);
	gen->generated += add;
	addstr = ft_itoa(add);
	extra = (t_string){0};
	extra.str = ft_strjoin("+", addstr);
	extra.color = 0xFFFFFF;
	extra.size = 0.5;
	extra.x = 80;
	extra.y = 60;
	extra.time = 1000;
	extra.background = 0x2A2E37;
	extra.padding = 1;
	render_string_async(&extra);
	ft_free(addstr);
}

void	generator_generating(t_async *current)
{
	t_generator	*gen;
	double		money_to_add;
	int			x;

	if (is_paused())
		return ;
	gen = (t_generator *)current->arg;
	pthread_mutex_lock(&gen->mutex);
	money_to_add = (gen->add_money / 5.0) * gen->speed;
	add_money(money_to_add);
	gen->generated += money_to_add;
	x = random_int(gen->random * 5, 100);
	if (gen->random > 0 && x == 100)
		generator_add_money(gen);
	pthread_mutex_unlock(&gen->mutex);
}
