/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:39:01 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 17:45:19 by escura           ###   ########.fr       */
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
	put_string("WHAT IS ... ?", x + 90, y + 10, 0x7dd3fc, 1);
	put_string(temp, x + 220, y + 50, 0xfb7185, 0.5);
	put_string(str3, x + 180, y + 100, 0x00FF00, 0.8);
	ft_free(temp);
	ft_free(num1);
	ft_free(str);
	ft_free(str2);
	ft_free(str3);
}

static void	select_math(void *arg)
{
	player()->math_selected = (int)arg;
}

static void	choice_button(int x, int y, int i)
{
	const t_player	*p = player();
	t_button		button;

	button = (t_button){0};
	button.x = x + 12 + (i * 200);
	button.y = y + 200;
	button.size = 2;
	button.is_default = true;
	button.function = &select_math;
	button.arg = p->random[i];
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
	const t_texture	*window = textures()->ui->window;
	const int		x = CENTER_WIDTH - window->width / 2;
	const int		y = CENTER_HEIGHT - window->height / 2;

	player()->mouse_hook = false;
	window_gui(x, y, window);
	choices(x, y);
}
