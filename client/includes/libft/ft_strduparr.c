/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strduparr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:17:33 by escura            #+#    #+#             */
/*   Updated: 2024/05/03 13:44:45 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include "libft.h"

void ft_clean_arr(char **arr)
{
    int i = 0;
    while (arr[i] != NULL)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

char	**ft_strduparr(const char **src)
{
    int size = 0;
    while (src[size] != NULL) {
        size++;
    }

    char **new_arr = malloc((size + 1) * sizeof(char *));
    if (!new_arr)
        return NULL;

    int i = 0;
    while (i < size) {
        new_arr[i] = ft_strdup(src[i]);
        if (!new_arr[i]){
            ft_clean_arr(new_arr);
            return NULL;
        }
        i++;
    }
    new_arr[size] = NULL;

    return new_arr;
}