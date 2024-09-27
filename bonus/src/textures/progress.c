/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:35:26 by escura            #+#    #+#             */
/*   Updated: 2024/09/24 21:19:03 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_progress(t_textures *t)
{
	int		i;
	char	*path;

	i = 0;
	while (i < 24)
	{
		path = get_texture_name("assets/UI/progress/", i);
		t->ui->progress[i] = *load_texture(path);
		i++;
		ft_free(path);
	}
	i = 0;
	while (i < 3)
	{
		path = get_texture_name("assets/UI/progress/cover/", i);
		t->ui->progress_cover[i] = *load_texture(path);
		i++;
		ft_free(path);
	}
}

t_texture	*progress_bar(int progress, int color)
{
	t_textures	*t;

	t = textures();
	if (color == PROGRESS_COVER)
	{
		if (progress > 2 || progress < 0)
			return (NULL);
		return (&(t->ui->progress_cover[progress]));
	}
	if (progress + color > 24 || progress + color < 0)
		return (NULL);
	return (&(t->ui->progress[progress + color]));
}
