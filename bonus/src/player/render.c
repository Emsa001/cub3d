/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:08:59 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 19:54:40 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_cross_in_centre(t_render *r)
{
	const int	x_center = WIDTH / 2;
	const int	y_center = HEIGHT / 2;
	int			i;

	i = -7;
	while (i <= 7)
	{
		put_pixel(x_center + i, y_center, 0x0000FF00, r);
		put_pixel(x_center, y_center + i, 0x0000FF00, r);
		i++;
	}
}

static t_texture	*render_hand_utils(t_texture *handtexture, t_player *p)
{
	static int	x = 0;
	t_texture	*rotated_hand;
	int			xpos;
	int			ypos;

	xpos = 500;
	ypos = 600;
	if (p->swing)
	{
		rotated_hand = rotate_texture(handtexture, sin(x * 0.1) * -40,
				HORIZONTAL_MIRROR);
		xpos = 650;
		ypos = 650;
		if (x > 20)
		{
			p->swing = false;
			x = 0;
		}
		x++;
	}
	else
		rotated_hand = rotate_texture(handtexture, 0, HORIZONTAL_MIRROR);
	put_image(rotated_hand, WIDTH - xpos, HEIGHT - ypos, 20);
	return (rotated_hand);
}

void	render_hand_item(void)
{
	const t_textures	*t = textures();
	t_player			*p;
	t_item				*item;
	t_texture			*rotated_hand;

	p = player();
	item = p->hand;
	if (item == NULL)
		return ;
	rotated_hand = render_hand_utils(&(t->items[item->props.id]), p);
	destroy_texture(rotated_hand);
	ft_free(rotated_hand);
}

void	render_player(void)
{
	t_player	*p;

	p = player();
	destroy_buttons();
	// render_minimap();
	hud_inventory();
	hud_currency();
	if (p->GUI == INVENTORY)
		open_inventory();
	else if (is_paused())
		pause_game();
	render_hand_item();
}
