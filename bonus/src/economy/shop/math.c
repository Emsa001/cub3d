/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:39:01 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:21:26 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	window_gui(int x, int y, t_texture *window)
{
	char *const	temp = ft_strjoin_itoa("Streak: ", player()->streak);
	char *const	num1 = ft_itoa(player()->math[0]);
	char *const	str = ft_strjoin(num1, " + ");
	char *const	str2 = ft_strjoin_itoa(str, player()->math[1]);
	char *const	str3 = ft_strjoin(str2, " = ?");

	put_image(window, x, y, 1);
	render_string(&(t_string){.str = "WHAT IS ... ?", .color = 0x7dd3fc,
		.size = 1, .x = x + 90, .y = y + 10});
	put_string(temp, x + 220, y + 50, 0xfb7185);
	render_string(&(t_string){.str = str3, .color = 0x00FF00, .size = 0.8,
		.x = x + 180, .y = y + 100});
	ft_free(temp);
	ft_free(num1);
	ft_free(str);
	ft_free(str2);
	ft_free(str3);
}

static void	select_math(void *arg)
{
	player()->math_selected = (intptr_t)arg;
}

static void	choice_button(int x, int y, int i)
{
	t_player *const	p = player();
	t_button		button;

	button = (t_button){0};
	button.x = x + 12 + (i * 200);
	button.y = y + 200;
	button.size = 2;
	button.is_default = true;
	button.left_click = &select_math;
	button.arg = (void *)(intptr_t)(p->random[i]);
	add_button(&button);
	if (p->hover != NULL && p->hover->x == button.x && p->hover->y == button.y
		|| p->math_selected == p->random[i])
		put_image(textures()->ui->button_hover, button.x, button.y,
			button.size);
}

static void	choices(int x, int y)
{
	const t_player	*p = player();
	char			*num;
	int				i;
	float			size;
	t_string		string;

	i = 0;
	while (i < 3)
	{
		choice_button(x, y, i);
		num = ft_itoa(p->random[i]);
		size = 2;
		if (ft_strlen(num) > 1)
			size = 1.4;
		string = (t_string){0};
		string.str = num;
		string.color = 0x00FF00;
		string.size = size;
		string.x = (x + 12 + (i * 200)) + (180 / 2) - ((ft_strlen(num) * size
					* 32) / 2);
		string.y = (y + 200) + 56;
		render_string(&string);
		ft_free(num);
		i++;
	}
}

void	math_gui(void)
{
	t_texture *const	window = textures()->ui->window;
	const int			x = CENTER_WIDTH - window->width / 2;
	const int			y = CENTER_HEIGHT - window->height / 2;

	player()->mouse_hook = false;
	window_gui(x, y, window);
	choices(x, y);
}
