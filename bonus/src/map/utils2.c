/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btvildia <btvildia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:48:01 by btvildia          #+#    #+#             */
/*   Updated: 2024/10/01 13:12:57 by btvildia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_c(char **map, char c)
{
	int	i;
	int	j;
	int	zero;

	i = 0;
	j = 0;
	zero = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == c)
				zero++;
			j++;
		}
		i++;
	}
	return (zero);
}

float	ft_parse_integer_part(char *str, int *i, int *sign)
{
	float	res;

	res = 0;
	*sign = 1;
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	while (str[*i] != '.' && str[*i] != '\0' && str[*i] != '\n')
	{
		res = res * 10 + str[*i] - '0';
		(*i)++;
	}
	return (res);
}

float	ft_parse_decimal_part(char *str, int i)
{
	float	dec;
	int		j;

	dec = 0;
	j = 0;
	if (str[i] == '.')
	{
		i++;
		while (str[i] != '\0' && str[i] != '\n')
		{
			dec = dec * 10 + str[i] - '0';
			i++;
			j++;
		}
	}
	while (j > 0)
	{
		dec = dec / 10;
		j--;
	}
	return (dec);
}

float	ft_float_atoi(char *str)
{
	float	res;
	float	dec;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	res = ft_parse_integer_part(str, &i, &sign);
	dec = ft_parse_decimal_part(str, i);
	return (sign * (res + dec));
}
