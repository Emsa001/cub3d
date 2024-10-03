/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:03:04 by escura            #+#    #+#             */
/*   Updated: 2024/10/03 19:14:26 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	vert_offset(const t_player *p)
{
	return ((p->z_dir) * HEIGHT);
}

float	view_current_distance(const t_player *p, int start_y, float angle)
{
	float	z;
	float	current_dist;

	z = 1;
	if (start_y >= HEIGHT / 2)
		z = 0;
	current_dist = (p->z - z) * HEIGHT / (start_y - HEIGHT / 2);
	return (current_dist / cos(angle - p->angle));
}

t_texture	*get_texture(int start_y, int height, t_thread_params *p)
{
	if (start_y > HEIGHT / 2 + (p->player->z * height))
	{
		return (p->textures->floor[player()->level]);
	}
	else if (start_y < ((p->player->z * height) + HEIGHT / 2) - height)
	{
		return (p->textures->ceiling[player()->level]);
	}
	return (NULL);
}

int	get_texture_color(t_texture *tex, float dist, t_draw *draw)
{
	float	tex_x;
	float	tex_y;
	int		color;

	tex_x = player()->x + dist * draw->cosangle;
	tex_y = player()->y + dist * draw->sinangle;
	color = get_pixel_from_image(tex, tex_x * T_SIZE, tex_y * T_SIZE);
	color = darken_color_wall(color, (float)dist / 7, tex_x, tex_y);
	return (color);
}
