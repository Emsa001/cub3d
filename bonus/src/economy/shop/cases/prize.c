/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prize.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:27:23 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:04:43 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_display_text(int prize, int value)
{
	char		*display_text;
	char *const	remove_money_str = ft_itoa(prize - value);

	if (prize - value > 0)
		display_text = ft_strjoin("+", remove_money_str);
	else
		return (remove_money_str);
	ft_free(remove_money_str);
	return (display_text);
}

void	display_prize_message(int prize, int value)
{
	t_string	string;
	char *const	display_text = get_display_text(prize, value);

	if (display_text == NULL)
		return ;
	string = (t_string){0};
	string.str = ft_strdup(display_text);
	string.color = 0xFFFFFF;
	string.size = 0.4;
	string.x = 80;
	string.y = 60;
	string.time = 1000;
	render_string_async(&string);
	string.str = "You got";
	string.size = 2;
	string.x = CENTER_WIDTH - ft_strlen(string.str) * 20;
	string.y = CENTER_HEIGHT - 250;
	render_string_async(&string);
	string.str = display_text;
	string.y = CENTER_HEIGHT + 120;
	render_string_async(&string);
}

t_texture	*determine_prize_texture(int prize)
{
	t_textures *const	t = textures();
	t_texture			*prize_texture;

	prize_texture = &(t->items[66]);
	if (prize > 70000)
		prize_texture = &(t->items[70]);
	else if (prize > 50000)
		prize_texture = &(t->items[69]);
	else if (prize > 20000)
		prize_texture = &(t->items[68]);
	else if (prize > 5000)
		prize_texture = &(t->items[67]);
	return (prize_texture);
}

void	render_prize_image(t_texture *prize_texture, int time)
{
	t_image	prize_image;

	prize_image = (t_image){0};
	prize_image.img = prize_texture;
	prize_image.x = CENTER_WIDTH - 100;
	prize_image.y = CENTER_HEIGHT - 200;
	prize_image.size = 10;
	prize_image.time = time;
	render_image_async(&prize_image);
}
