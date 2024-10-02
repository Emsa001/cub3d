/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 15:34:36 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 00:06:42 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://stmn.itch.io/font2bitmap
#include "cub3d.h"

static void	draw_character_scaled(t_string_params *params, int i, int j)
{
	float	dx;
	float	dy;

	dx = 0;
	dy = 0;
	while (dx < params->size)
	{
		dy = 0;
		while (dy < params->size)
		{
			put_pixel((params->x + i * params->size) + dx, (params->y + j
					* params->size) + dy, params->color, render());
			dy++;
		}
		dx++;
	}
}

static void	draw_character(t_string_params *params)
{
	const int	*pixels = textures()->char_pixel_data[params->char_index];
	int			i;
	int			j;

	i = 0;
	while (i < CHAR_WIDTH)
	{
		j = 0;
		while (j < CHAR_HEIGHT)
		{
			if (pixels[i + j * CHAR_WIDTH] > 0)
				draw_character_scaled(params, i, j);
			j++;
		}
		i++;
	}
}

void	render_string(t_string *s)
{
	t_string_params	params;
	char			ch;

	if (s->background != false)
		draw_background(s);
	params.x = s->x;
	params.y = s->y;
	params.color = s->color;
	params.size = s->size;
	while (*s->str)
	{
		ch = *(s->str)++;
		if (ch < ' ' || ch > '~')
			continue ;
		params.char_index = ch - ' ';
		draw_character(&params);
		params.x += CHAR_WIDTH * s->size;
	}
}

void	put_string(char *str, int x, int y, int color)
{
	t_string	string;

	string = (t_string){0};
	string.str = str;
	string.x = x;
	string.y = y;
	string.color = color;
	string.size = 0.5;
	string.padding = 0;
	render_string(&string);
}
