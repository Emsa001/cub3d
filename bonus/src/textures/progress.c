/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:35:26 by escura            #+#    #+#             */
/*   Updated: 2024/09/19 16:22:12 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_progress(t_textures *t)
{
	int i = 0;
	while(i < 24){
        char *name = "assets/UI/progress/";
        char *num = ft_itoa(i);
        char *ext = ".xpm";
        char *path = ft_strjoin(name, num);
        char *path2 = ft_strjoin(path, ext);


		t_texture key = {0};
		key.image = get_texture_file(path2, &key.width, &key.height);
		key.data = mlx_get_data_addr(key.image, &key.bpp, &key.size_line, &key.endian);
		t->ui->progress[i] = key;
		i++;

		ft_free(num);
        ft_free(path);
        ft_free(path2);
	}

	i = 0;
	while(i < 3){
        char *name = "assets/UI/progress/cover/";
        char *num = ft_itoa(i);
        char *ext = ".xpm";
        char *path = ft_strjoin(name, num);
        char *path2 = ft_strjoin(path, ext);


		t_texture key = {0};
		key.image = get_texture_file(path2, &key.width, &key.height);
		key.data = mlx_get_data_addr(key.image, &key.bpp, &key.size_line, &key.endian);
		t->ui->progress_cover[i] = key;
		i++;

		ft_free(num);
        ft_free(path);
        ft_free(path2);
	}
}

t_texture *progress_bar(int progress, int color)
{
    t_textures *t = textures();

    if(color == PROGRESS_COVER){
        if(progress > 2 || progress < 0)
            return NULL;
        return &(t->ui->progress_cover[progress]);
    }

    if(progress + color > 24 || progress + color < 0)
        return NULL;
    return &(t->ui->progress[progress + color]);
}