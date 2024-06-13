/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:41:51 by btvildia          #+#    #+#             */
/*   Updated: 2024/06/13 21:18:13 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_map_sizes(t_map *map_info, char **map)
{
    int i = 0;
    int max_width = 0;
    int height = 0;

    while (map[i] != NULL) 
    {
        char *line = map[i];
        int start = 0;
        int end = strlen(line) - 1;

        while (start <= end && ft_isspace(line[start]))
            start++;
        while (end >= start && ft_isspace(line[end]))
            end--;
        if (start <= end && line[start] == '1' && line[end] == '1') 
        {
            height++;
            int line_length = end - start + 1;
            if (line_length > max_width) 
                max_width = line_length;
        }
        i++;
    }
    map_info->width = max_width;
    map_info->height = height;
}

void get_no_so_we_ea(t_map *map_info, char **map)
{
    int i = 0;
    while (map[i] != NULL) 
    {
        char *line = map[i];
        if (ft_strncmp(line, "NO ", 3) == 0) 
            map_info->no = ft_strdup(line + 3);
        else if (ft_strncmp(line, "SO ", 3) == 0) 
            map_info->so = ft_strdup(line + 3);
        else if (ft_strncmp(line, "WE ", 3) == 0) 
            map_info->we = ft_strdup(line + 3);
        else if (ft_strncmp(line, "EA ", 3) == 0) 
            map_info->ea = ft_strdup(line + 3);
        else if (ft_strncmp(line, "F ", 2) == 0) 
        {
            char **rgb = ft_split(line + 2, ',');
            map_info->f[0] = ft_atoi(rgb[0]);
            map_info->f[1] = ft_atoi(rgb[1]);
            map_info->f[2] = ft_atoi(rgb[2]);
            ft_free_arr(rgb);
        }
        else if (ft_strncmp(line, "C ", 2) == 0) 
        {
            char **rgb = ft_split(line + 2, ',');
            map_info->c[0] = ft_atoi(rgb[0]);
            map_info->c[1] = ft_atoi(rgb[1]);
            map_info->c[2] = ft_atoi(rgb[2]);
            ft_free_arr(rgb);
        }
        i++;
    }
}

void get_player_position(t_map *map_info)
{
    int i = 0;
    int j = 0;
    while (map_info->map[i] != NULL) 
    {
        j = 0;
        while (map_info->map[i][j] != '\0') 
        {
            if (map_info->map[i][j] == 'N' || map_info->map[i][j] == 'S' || map_info->map[i][j] == 'W' || map_info->map[i][j] == 'E') 
            {
                map_info->player_x = j + 0.5;
                map_info->player_y = i + 0.5;
                if (map_info->map[i][j] == 'N')
                    map_info->player_a = 3 * PI / 2;
                else if (map_info->map[i][j] == 'S')
                    map_info->player_a = PI / 2;
                else if (map_info->map[i][j] == 'W')
                    map_info->player_a = PI;
                else if (map_info->map[i][j] == 'E')
                    map_info->player_a = 0;
                return;
            }
            j++;
        }
        i++;
    }
    ft_error("Player not found");
}

void get_2d_map(t_map *map_info, char **map)
{
    int i = 0;
    int j = 0;
    map_info->map = ft_malloc(sizeof(char *) * (map_info->height + 1));
    while (map[i] != NULL) 
    {
        char *line = map[i];
        int start = 0;
        int end = strlen(line) - 1;

        while (start <= end && ft_isspace(line[start]))
            start++;
        while (end >= start && ft_isspace(line[end]))
            end--;
        if (start <= end && line[start] == '1' && line[end] == '1') 
        {
            map_info->map[j] = ft_strdup(line);
            j++;
        }
        i++;
    }
    map_info->map[j] = NULL;
}

t_map *check_map(char **map)
{
    t_map *map_info = ft_malloc(sizeof(t_map));
    map_info->width = 0;
    map_info->height = 0;
    map_info->no = NULL;
    map_info->so = NULL;
    map_info->we = NULL;
    map_info->ea = NULL;
    map_info->f = ft_malloc(sizeof(int) * 3);
    map_info->f[0] = -1;
    map_info->f[1] = -1;
    map_info->f[2] = -1;
    map_info->c = ft_malloc(sizeof(int) * 3);
    map_info->c[0] = -1;
    map_info->c[1] = -1;
    map_info->c[2] = -1;
    map_info->player_x = -1;
    map_info->player_y = -1;
    map_info->player_a = -1;    
    get_no_so_we_ea(map_info, map);
    get_map_sizes(map_info, map);
    get_2d_map(map_info, map);
    get_player_position(map_info);
    return (map_info);
}
