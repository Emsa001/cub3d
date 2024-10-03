/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:09:10 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:55:01 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	item_button(t_button *button, float size)
{
	t_textures *const	t = textures();
	t_player *const		p = player();
	t_texture const item_texture = t->items[button->item_id];
	const int			item_x = button->x + (button->width - item_texture.width * size * 2) / 2;
	const int			item_y = button->y + (button->height - item_texture.height * size * 2.3) / 2;

	if (p->hover && p->hover->x == button->x && p->hover->y == button->y)
		put_image(t->ui->button_hover, button->x, button->y, size);
	else
		put_image(t->ui->button, button->x, button->y, size);
	put_image((t_texture *)(&item_texture), item_x, item_y, size * 2);
}
