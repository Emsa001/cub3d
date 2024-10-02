/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:29:41 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:59:51 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	timer_process(t_async *async)
{
	t_string	str;
	char *const	time = ft_itoa((async->time - async->time_elapsed) / 1000);

	str = (t_string){0};
	str.str = time;
	str.x = ((t_location *)async->arg)->x;
	str.y = ((t_location *)async->arg)->y;
	str.color = 0xc2410c;
	str.size = 3;
	str.time = 1000;
	render_string_async(&str);
}

void	string_timer(int time, t_location *location)
{
	t_async *const	async = new_async();

	async->process = &timer_process;
	async->process_time = 1000;
	async->arg = (void *)(location);
	async->time = time;
	start_async(async);
}

void	interaction_notify(char *str)
{
	const t_texture	*t = textures()->ui->button_long;
	const int		length = ft_strlen(str);
	int				i;
	t_string		notify;

	notify = (t_string){0};
	notify.str = str;
	notify.color = 0xeab308;
	notify.size = 0.7;
	notify.x = CENTER_WIDTH - 330;
	notify.y = HEIGHT - 100;
	i = 0;
	while (i < length / 5)
	{
		put_image(t, CENTER_WIDTH - 400 + (i * t->width * 0.7 - ((i - 1) * 4)),
			HEIGHT - 115, 0.7);
		i++;
	}
	render_string(&notify);
}

void	draw_background(t_string *s)
{
	const int	background_width = (CHAR_WIDTH * ft_strlen(s->str) * s->size)
		+ s->padding * 2;
	const int	background_height = (CHAR_HEIGHT * s->size) + s->padding * 2;
	int			i;
	int			j;

	i = 0;
	while (i < background_width)
	{
		j = 0;
		while (j < background_height)
		{
			put_pixel(s->x + i - s->padding, s->y + j - s->padding,
				s->background, render());
			j++;
		}
		i++;
	}
}
