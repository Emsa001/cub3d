/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:52:13 by escura            #+#    #+#             */
/*   Updated: 2024/10/07 18:00:26 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	generator_async_init(t_generator *gen)
{
	t_async	*async;

	async = new_async();
	async->process = &generator_generating;
	async->process_time = 1000;
	async->arg = (void *)gen;
	async->time = -1;
	async->cube = cube();
	async->player = player();
	start_async(async);
}

t_generator	*create_generator(int x, int y)
{
	t_generator	*gen;

	printf("DEBUG: Created generator at %d %d\n", x, y);
	gen = ft_calloc(1, sizeof(t_generator));
	gen->x = x;
	gen->y = y;
	gen->generated = 0;
	gen->add_money = 10;
	gen->random = 0;
	gen->level = 1;
	gen->speed = 1;
	gen->loop = 0;
	gen->next = NULL;
	pthread_mutex_init(&gen->mutex, NULL);
	cube()->add_money += gen->add_money;
	generator_async_init(gen);
	return (gen);
}

t_generator	*get_generator(int x, int y)
{
	t_generator	*gen;
	t_generator	*last_gen;

	gen = player()->store->generators;
	last_gen = NULL;
	while (gen)
	{
		if (gen->x == x && gen->y == y)
			return (gen);
		last_gen = gen;
		gen = gen->next;
	}
	gen = create_generator(x, y);
	if (player()->store->generators == NULL)
		player()->store->generators = gen;
	else
		last_gen->next = gen;
	return (gen);
}

int	gen_total_amount(void)
{
	t_generator	*gen;
	int			total;

	gen = player()->store->generators;
	total = 0;
	while (gen)
	{
		total += (gen->add_money / 5) * gen->speed;
		gen = gen->next;
	}
	return (total);
}
