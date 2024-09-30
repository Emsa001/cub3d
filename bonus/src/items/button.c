/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:09:10 by escura            #+#    #+#             */
/*   Updated: 2024/09/30 15:46:34 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	item_button(t_button *button, float size)
{
	const t_textures	*t = textures();
	const t_player		*p = player();
	const t_texture		item_texture = t->items[button->itemId];
	const int			item_x = button->x + (button->width - item_texture.width
			* size * 2) / 2;
	const int			item_y = button->y + (button->height
			- item_texture.height * size * 2.3) / 2;

	if (p->hover && p->hover->x == button->x && p->hover->y == button->y)
		put_image(t->ui->button_hover, button->x, button->y, size);
	else
		put_image(t->ui->button, button->x, button->y, size);
	put_image(&item_texture, item_x, item_y, size * 2);
}
