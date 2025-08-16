/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:44:46 by escura            #+#    #+#             */
/*   Updated: 2024/09/24 19:47:07 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_rotate_vars	*rotate_image_init(t_texture *src, t_texture *dest,
		double angle)
{
	t_rotate_vars	*v;

	v = ft_malloc(sizeof(t_rotate_vars));
	v->red_angle = deg_to_rad(angle);
	v->cos_a = cos(v->red_angle);
	v->sin_a = sin(v->red_angle);
	v->src_cx = src->width / 2;
	v->src_cy = src->height / 2;
	v->dest_cx = dest->width / 2;
	v->dest_cy = dest->height / 2;
	v->y = 0;
	v->i = 0;
	return (v);
}

static void	rotate_image_1(t_rotate_vars *v, t_texture *src, t_texture *dest)
{
	const int	src_x = (int)((v->tx - v->dest_cx) * v->cos_a - (v->ty
				- v->dest_cy) * v->sin_a + v->src_cx);
	const int	src_y = (int)((v->tx - v->dest_cx) * v->sin_a + (v->ty
				- v->dest_cy) * v->cos_a + v->src_cy);

	if (src_x >= 0 && src_x < src->width && src_y >= 0 && src_y < src->height)
	{
		v->src_offset = src_y * src->size_line + src_x * (src->bpp / 8);
		v->dest_offset = v->y * dest->size_line + v->x * (dest->bpp / 8);
		v->i = 0;
		while (v->i < src->bpp / 8)
		{
			dest->data[v->dest_offset + v->i] = src->data[v->src_offset + v->i];
			v->i++;
		}
	}
	else
	{
		v->dest_offset = v->y * dest->size_line + v->x * (dest->bpp / 8);
		v->i = 0;
		while (v->i < src->bpp / 8)
			dest->data[v->dest_offset + (v->i++)] = 0xFF;
	}
}

void	rotate_image(t_texture *src, t_texture *dest, double angle, int mirror)
{
	t_rotate_vars	*v;

	v = rotate_image_init(src, dest, angle);
	while (v->y < dest->height)
	{
		v->x = 0;
		while (v->x < dest->width)
		{
			v->tx = v->x;
			v->ty = v->y;
			if (mirror == HORIZONTAL_MIRROR || mirror == BOTH_MIRROR)
				v->tx = dest->width - 1 - v->x;
			if (mirror == VERTICAL_MIRROR || mirror == BOTH_MIRROR)
				v->ty = dest->height - 1 - v->y;
			rotate_image_1(v, src, dest);
			v->x++;
		}
		v->y++;
	}
	ft_free(v);
}

t_texture	*rotate_texture(t_texture *texture, double angle, int mirror)
{
	const double	rad_angle = deg_to_rad(angle);
	const double	new_width = fabs(texture->width * cos(rad_angle))
		+ fabs(texture->height * sin(rad_angle));
	const double	new_height = fabs(texture->width * sin(rad_angle))
		+ fabs(texture->height * cos(rad_angle));
	t_texture		*rotated_texture;

	rotated_texture = ft_malloc(sizeof(t_texture));
	rotated_texture->image = mlx_new_image(render()->mlx, new_width,
			new_height);
	rotated_texture->data = mlx_get_data_addr(rotated_texture->image,
			&rotated_texture->bpp, &rotated_texture->size_line,
			&rotated_texture->endian);
	rotated_texture->width = new_width;
	rotated_texture->height = new_height;
	rotate_image(texture, rotated_texture, angle, mirror);
	return (rotated_texture);
}
