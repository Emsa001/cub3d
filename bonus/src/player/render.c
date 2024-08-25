/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:08:59 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 18:56:44 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static void draw_cross_in_centre(t_render *r)
{
    int x_center = WIDTH / 2;
    int y_center = HEIGHT / 2;
    int i = -7;

	while (i <= 7)
	{
		put_pixel(x_center + i, y_center, 0x0000FF00, r);
		put_pixel(x_center, y_center + i, 0x0000FF00, r);
		i++;
	}
}

void render_hand_item()
{
	static int x = 0;
	t_player *p = player();
	t_item *item = p->hand;
	
	if(item == NULL)
		return;
	
	t_texture *hand = textures()->items[item->props.id];
	t_texture *rotated_hand;
	
	int xpos = 500;
	int ypos = 600;

	if(p->swing){
		rotated_hand = rotate_texture(hand, sin(x * 0.1) * -20, HORIZONTAL_MIRROR);
		xpos = 650;
		ypos = 650;
		if(x > 20){
			p->swing = false;
			x = 0;
		}
		x++;
	}else{
		rotated_hand = rotate_texture(hand, 0, HORIZONTAL_MIRROR);
	}

	put_image(rotated_hand, WIDTH - xpos, HEIGHT - ypos, 20);
	destroy_image(rotated_hand->image);
	ft_free(rotated_hand);
}

void render_player(){
    // draw_cross_in_centre(render());
	destroy_buttons();
	render_hud();
	render_hand_item();
}