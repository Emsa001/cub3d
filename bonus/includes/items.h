/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:19:57 by escura            #+#    #+#             */
/*   Updated: 2024/08/25 19:08:17 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# define BOOTS 3
# define WEAPON 4

typedef struct s_cube t_cube;

typedef struct s_itemprops
{
	int			id;
	int			slot;
	int			effect;
	int			playerslot;
}				t_itemprops;

typedef struct s_item
{
	char		*name;
	float		fontSize;
	void		(*use)(t_itemprops props);
	t_itemprops	props;
}				t_item;

void			init_items(void);
void			init_weapons(t_cube *c);
void			init_potions(t_cube *c);
void			init_armor(t_cube *c);

void			instand_death(t_itemprops props);
void			cure(t_itemprops props);
void			vision(t_itemprops props);
void			equip(t_itemprops props);
void			unequip(void *props);

void			useItem(void *arg);

#endif