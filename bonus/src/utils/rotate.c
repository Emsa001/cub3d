/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:44:46 by escura            #+#    #+#             */
/*   Updated: 2024/09/12 14:34:15 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DEG_TO_RAD(angle) ((angle) * M_PI / 180.0)

void rotate_image(t_texture *src, t_texture *dest, double angle, int mirror_mode)
{
	double rad_angle = DEG_TO_RAD(angle);
	double cos_a = cos(rad_angle);
	double sin_a = sin(rad_angle);

	int src_cx = src->width / 2;
	int src_cy = src->height / 2;
	int dest_cx = dest->width / 2;
	int dest_cy = dest->height / 2;

	for (int y = 0; y < dest->height; y++)
	{
		for (int x = 0; x < dest->width; x++)
		{
			// Apply mirror mode
			int tx = x;
			int ty = y;
			if (mirror_mode == HORIZONTAL_MIRROR || mirror_mode == BOTH_MIRROR)
				tx = dest->width - 1 - x;
			if (mirror_mode == VERTICAL_MIRROR || mirror_mode == BOTH_MIRROR)
				ty = dest->height - 1 - y;

			// Calculate the corresponding source coordinates
			int src_x = (int)((tx - dest_cx) * cos_a - (ty - dest_cy) * sin_a + src_cx);
			int src_y = (int)((tx - dest_cx) * sin_a + (ty - dest_cy) * cos_a + src_cy);

			// Check boundaries and copy pixel data
			if (src_x >= 0 && src_x < src->width && src_y >= 0 && src_y < src->height)
			{
				int src_offset = src_y * src->size_line + src_x * (src->bpp / 8);
				int dest_offset = y * dest->size_line + x * (dest->bpp / 8);

				for (int i = 0; i < src->bpp / 8; i++)
				{
					dest->data[dest_offset + i] = src->data[src_offset + i];
				}
			}
			else
			{
				// Optional: Set a default color for out-of-bounds pixels
				int dest_offset = y * dest->size_line + x * (dest->bpp / 8);
				for (int i = 0; i < src->bpp / 8; i++)
				{
					dest->data[dest_offset + i] = 0xFF; // white or transparent
				}
			}
		}
	}
}


t_texture *rotate_texture(t_texture *texture, double angle, int mirror_mode)
{
	double rad_angle = DEG_TO_RAD(angle);

	// Calculate the bounding box for the rotated image
	double new_width = fabs(texture->width * cos(rad_angle)) + fabs(texture->height * sin(rad_angle));
	double new_height = fabs(texture->width * sin(rad_angle)) + fabs(texture->height * cos(rad_angle));
	t_texture *rotated_texture = ft_malloc(sizeof(t_texture));

	// Create a new image for the rotated texture
	rotated_texture->image = mlx_new_image(render()->mlx, new_width, new_height);
	rotated_texture->data = mlx_get_data_addr(rotated_texture->image, &rotated_texture->bpp, &rotated_texture->size_line, &rotated_texture->endian);
	rotated_texture->width = new_width;
	rotated_texture->height = new_height;

	// Rotate and mirror the image
	rotate_image(texture, rotated_texture, angle, mirror_mode);

	return rotated_texture;
}
