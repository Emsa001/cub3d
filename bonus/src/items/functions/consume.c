/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consume.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:21:03 by escura            #+#    #+#             */
/*   Updated: 2024/09/26 19:29:07 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "items.h"

void consume(t_itemprops props)
{
    t_player	*p;

    p = player();

    printf("Consuming %d\n", props.id);
}