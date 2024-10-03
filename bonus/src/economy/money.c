/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   money.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:09:25 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:40:20 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_background_money(void)
{
	t_textures	*const	t = textures();
	int					i;

	i = 0;
	if (t->ui && t->ui->button)
	{
		while (i <= 3)
		{
			put_image(t->ui->button, (i * (t->ui->button->width - 15)), 5, 1);
			i++;
		}
	}
	put_image(&t->items[66], 10, 12, 2);
}

void	hud_currency(void)
{
	char			*money_srt;
	char			*add;

	draw_background_money();
	money_srt = ft_itoa(money());
	add = ft_itoa(gen_total_amount());
	put_string("+", 80, 15, 0xFFFFFF);
	put_string(add, 95, 15, 0xFFFFFF);
	put_string(money_srt, 80, 37, 0xffbf00);
	ft_free(money_srt);
	ft_free(add);
}

int	money(void)
{
	t_player	*p;
	int			money;

	p = player();
	pthread_mutex_lock(&p->money_mutex);
	money = p->money;
	pthread_mutex_unlock(&p->money_mutex);
	return (money);
}

void	add_money(int amount)
{
	t_player	*p;

	p = player();
	pthread_mutex_lock(&p->money_mutex);
	p->money += amount;
	pthread_mutex_unlock(&p->money_mutex);
}
