/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:02:34 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 18:51:33 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_items_textures(t_textures *t)
{
	char		*path;
	int			i;

	i = 0;
	while (i <= 327)
	{
		path = get_texture_name("assets/items/", i);
		t->items[i] = *load_texture(path);
		ft_free(path);
		i++;
	}
}
