/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:19:57 by escura            #+#    #+#             */
/*   Updated: 2024/08/24 19:24:19 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

typedef struct s_itemprops
{
    int id;
    int slot;   
    int effect; 
} t_itemprops;

typedef struct s_item
{
	void				(*use)(t_itemprops props);
	t_itemprops 		props;
}						t_item;

void init_items(void);
void instand_death(t_itemprops props);
void cure(t_itemprops props);
void equip(t_itemprops props);
void unequip(void *props);

void useItem(void *arg);

#endif