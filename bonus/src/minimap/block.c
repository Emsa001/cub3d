/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:52:56 by escura            #+#    #+#             */
/*   Updated: 2024/08/11 17:30:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	dst_texture(void)
{
	const t_texture		*src = textures()->wall_north;
	static t_texture	dst = {0};

	if (!dst.data)
	{
		dst.width = MINIMAP_BLOCK_SIZE;
		dst.height = MINIMAP_BLOCK_SIZE;
		dst.bpp = src->bpp;
		dst.size_line = dst.width * (dst.bpp / 8);
		dst.endian = src->endian;
		dst.data = (char *)ft_malloc(dst.size_line * dst.height);
		resize_texture(src, &dst, MINIMAP_BLOCK_SIZE, MINIMAP_BLOCK_SIZE);
	}
	return (dst);
}

static void	draw_block(int i, int j, int screen_x, int screen_y)
{
	t_render	*r = render();
	const t_texture	texture = dst_texture();
	const float		pixel_x = screen_x + i;
	const float		pixel_y = screen_y + j;
	const float		dx = pixel_x - minimap_center_x();
	const float		dy = pixel_y - minimap_center_y();

	if (dx * dx + dy * dy <= pow(minimap()->radius, 2))
		put_pixel((int)pixel_x, (int)pixel_y, get_pixel_from_image(&texture, i,
				j));
}

void	minimap_block(int x, int y, int screen_x, int screen_y)
{
	const t_texture	texture = dst_texture();
	int				j;
	int				i;

	j = 0;
	while (j < texture.height)
	{
		i = 0;
		while (i < texture.width)
		{
			draw_block(i, j, screen_x, screen_y);
			i++;
		}
		j++;
	}
}
