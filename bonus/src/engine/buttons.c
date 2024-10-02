/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:16:47 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 23:08:59 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	button_click(int type, int x, int y)
{
	t_button_node	*current;
	t_button		b;

	current = cube()->buttons;
	while (current != NULL)
	{
		b = current->button;
		if (x >= b.x && x <= b.x + b.width && y >= b.y && y <= b.y + b.height)
		{
			if (type == LEFT_CLICK && b.left_click != NULL)
				((void (*)(void *))b.left_click)(b.arg);
			if (type == RIGHT_CLICK && b.right_click != NULL)
				((void (*)(void *))b.right_click)(b.arg);
			return ;
		}
		current = current->next;
	}
}

void	button_hover(int x, int y)
{
	t_cube			*c;
	t_button_node	*current;
	t_button		b;

	c = cube();
	current = c->buttons;
	while (current != NULL)
	{
		b = current->button;
		if (x >= b.x && x <= b.x + b.width && y >= b.y && y <= b.y + b.height)
		{
			ft_free(player()->hover);
			player()->hover = ft_malloc(sizeof(t_button));
			ft_memcpy(player()->hover, &b, sizeof(t_button));
		}
		current = current->next;
	}
}

void	destroy_buttons(void)
{
	t_button_node	*current;
	t_button_node	*next;
	t_cube *const	c = cube();

	current = c->buttons;
	if (c->buttons == NULL)
		return ;
	while (current != NULL)
	{
		next = current->next;
		if (current != NULL)
			ft_free(current);
		current = next;
	}
	c->buttons = NULL;
}

static void	new_button_node(t_button *button)
{
	t_button_node	*node;
	t_button_node	*new_node;

	node = cube()->buttons;
	while (node != NULL)
	{
		if (ft_memcmp(&node->button, button, sizeof(t_button)) == 0)
			return ;
		node = node->next;
	}
	new_node = ft_malloc(sizeof(t_button_node));
	ft_memcpy(&new_node->button, button, sizeof(t_button));
	new_node->next = cube()->buttons;
	cube()->buttons = new_node;
}

void	add_button(t_button *button)
{
	const t_texture	*button_t = textures()->ui->button;

	if (button->is_default == true)
	{
		if (!button->size)
			button->size = 1;
		button->width = button_t->width * button->size;
		button->height = button_t->height * button->size;
	}
	new_button_node(button);
	if (button->is_default == true)
		put_image(button_t, button->x, button->y, button->size);
}
