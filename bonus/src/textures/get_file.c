/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 22:06:58 by escura            #+#    #+#             */
/*   Updated: 2024/10/05 19:56:18 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_path(char *path, int i)
{
	char	*num;
	char	*tmp;
	char	*tmp2;

	num = ft_itoa(i);
	tmp = ft_strjoin("assets/level", num);
	ft_free(num);
	tmp2 = ft_strjoin(tmp, "/");
	ft_free(tmp);
	tmp = ft_strjoin(tmp2, path);
	ft_free(tmp2);
	tmp2 = ft_strjoin(tmp, ".xpm");
	ft_free(tmp);
	return (tmp2);
}

void	*get_texture_file(char *file, int *width, int *height)
{
	void	*image;

	if (!file || open(file, O_RDONLY) < 0)
	{
		printf("Error\nInvalid texture file: %s\n", file);
		exit_game(1);
	}
	image = mlx_xpm_file_to_image(render()->mlx, file, width, height);
	return (image);
}

char	*get_texture_name(char *dir, int i)
{
	char	*num;
	char	*ext;
	char	*path;
	char	*path2;

	num = ft_itoa(i);
	ext = ".xpm";
	path = ft_strjoin(dir, num);
	path2 = ft_strjoin(path, ext);
	ft_free(num);
	ft_free(path);
	return (path2);
}

t_texture	*load_texture(char *dir)
{
	t_texture	*key;

	key = ft_calloc(1, sizeof(t_texture));
	key->image = get_texture_file(dir, &key->width, &key->height);
	if (key->image == NULL)
	{
		printf("Failed to get texture file: %s\n", dir);
		exit_game(1);
	}
	key->data = mlx_get_data_addr(key->image, &key->bpp, &key->size_line,
			&key->endian);
	if (key->data == NULL)
	{
		printf("Failed to get data address from image\n");
		exit_game(1);
	}
	return (key);
}
