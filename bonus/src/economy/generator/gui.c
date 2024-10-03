/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:24:31 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:22:30 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	info_gui(int x, int y, t_generator *gen)
{
	char *const	generated = ft_strjoin_itoa("Generated: ", gen->generated);
	char *const	random = ft_strjoin_itoa("Random: ", gen->random);
	char *const	add_temp = ft_strjoin_itoa("Generating: ", (gen->add_money / 5)
			* gen->speed);
	char *const	speed = ft_strjoin_itoa("Speed: ", gen->speed);
	char *const	add = ft_strjoin(add_temp, " / sec");

	put_string(add, x + 20, y + 160, 0x00FF00);
	put_string(generated, x + 20, y + 100, 0x00FF00);
	put_string(random, x + 20, y + 130, 0x00FF00);
	put_string(speed, x + 20, y + 190, 0x00FF00);
	ft_free(add_temp);
	ft_free(generated);
	ft_free(random);
	ft_free(add);
	ft_free(speed);
}

static void	window_gui(int x, int y, t_generator *gen)
{
	t_string	str;

	player()->mouse_hook = false;
	put_image(textures()->ui->window, x, y, 1);
	str = (t_string){0};
	str.str = "GENERATOR";
	str.color = 0x00FF00;
	str.size = 1.5;
	str.x = x + 90;
	str.y = y + 20;
	render_string(&str);
	pthread_mutex_lock(&gen->mutex);
	info_gui(x, y, gen);
	pthread_mutex_unlock(&gen->mutex);
}

static void	upgrades_2(int x, int y, t_generator *gen)
{
	t_generator_upgrade *const	random = ft_calloc(1,
			sizeof(t_generator_upgrade));
	t_generator_upgrade *const	speed = ft_calloc(1,
			sizeof(t_generator_upgrade));

	speed->level = &(gen->speed);
	speed->max_level = 5;
	speed->price = gen->speed * 10000;
	speed->prize = 1;
	speed->name = "Speed";
	generator_upgrade(x, y + 50, speed);
	random->level = &(gen->random);
	random->max_level = 11;
	random->price = gen->random * 50000;
	random->prize = 1;
	random->name = "Random";
	generator_upgrade(x + 200, y, random);
}

static void	upgrades(int x, int y, t_generator *gen)
{
	t_generator_upgrade *const	generating = ft_calloc(1,
			sizeof(t_generator_upgrade));

	generating->level = &(gen->level);
	generating->type = &(gen->add_money);
	generating->max_level = 5;
	generating->price = gen->level * 10000;
	generating->prize = gen->add_money * (gen->level + 1);
	generating->extra = UPDATE_ADD_MONEY;
	generating->name = "Generating";
	generator_upgrade(x, y, generating);
}

void	generator_gui(void)
{
	t_generator *const	gen = player()->generator;
	t_texture *const	window = textures()->ui->window;
	const int			x = CENTER_WIDTH - window->width / 2;
	const int			y = CENTER_HEIGHT - window->height / 2;

	window_gui(x, y, gen);
	upgrades(x, y, gen);
	upgrades_2(x, y, gen);
}
