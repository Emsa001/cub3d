/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healthbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:09:25 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 18:52:38 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fillbar(const t_render *r, const t_player *p, const t_textures *t)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < p->health * 2)
	{
		j = 0;
		while (j < t->healthbar->height)
		{
			color = get_pixel_from_image(t->healthbar, i, j);
			if (color > 0)
				put_pixel(i + 10, j + 10, color, r);
			j++;
		}
		i++;
	}
}

static void	hearticon(const t_player *p, const t_textures *t)
{
	t_texture	*icon;

	if (p->health > 0)
	{
		icon = NULL;
		if (p->health >= 90)
			icon = t->healthIcon[0];
		else if (p->health >= 75)
			icon = t->healthIcon[1];
		else if (p->health >= 50)
			icon = t->healthIcon[2];
		else if (p->health >= 25)
			icon = t->healthIcon[3];
		if (icon != NULL)
			put_image(icon, 10, 10, 1);
	}
}

void	hud_healthbar(void)
{
	const t_textures *t = textures();
	const t_player *p = player();
	const t_render *r = render();

	put_image(t->healthhud, 10, 10, 1);
	fillbar(r, p, t);
	hearticon(p, t);
}