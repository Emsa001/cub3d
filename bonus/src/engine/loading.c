/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 21:44:10 by escura            #+#    #+#             */
/*   Updated: 2024/10/04 22:26:38 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loading_end()
{
	t_render *const r = render();
    stop_all_async_tasks();
	r->loading = false;
}

static void loading_buttons()
{
	t_string str;

	str = (t_string){0};
	str.str = "Press any key to start";
	str.color = 0xFFFFFF;
	str.size = 0.6;
	str.x = WIDTH / 2 - ft_strlen(str.str) * 9;
	str.y = HEIGHT - 170;
	str.background = 0x000001;
	str.padding = 10;
	str.time = -1;
	str.animation = 10;
	str.blink = 120;
	render_string_async(&str);
	cube()->accept_hooks = true;
}

static void loadin_authors()
{
	t_string str;

	str = (t_string){0};
	str.str = "by Emanuel and Beqa";
	str.color = 0xFFFFFF;
	str.size = 0.6;
	str.x = WIDTH / 2 - ft_strlen(str.str) * 9;
	str.y = HEIGHT / 2 - 50;
	str.time = -1;
	str.animation = 10;
	render_string_async(&str);
}

void	loading_screen(void)
{
	t_string	str;

	str = (t_string){0};
	str.str = "The Game";
	str.color = 0xFFFFFF;
	str.size = 3;
	str.x = WIDTH / 2 - ft_strlen(str.str) * 48;
	str.y = HEIGHT / 2 - 200;
	str.time = -1;
	str.animation = 30;
	render_string_async(&str);

	ft_wait(1500, loadin_authors, NULL);
	ft_wait(3000, loading_buttons, NULL);
}
