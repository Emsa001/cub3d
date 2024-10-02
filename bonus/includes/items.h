/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: escura <escura@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 18:19:57 by escura            #+#    #+#             */
/*   Updated: 2024/10/02 18:20:01 by escura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITEMS_H
# define ITEMS_H

# define BOOTS 3
# define WEAPON 4

typedef struct s_cube	t_cube;
typedef struct s_item	t_item;

typedef struct s_itemprops
{
	int					id;
	int					slot;
	int					effect;
	int					time;
	int					*intvar;
	int					playerslot;
}						t_itemprops;

typedef struct s_item
{
	char				*name;
	float				font_size;
	void				(*use)(t_itemprops props);
	void				(*right_click)(t_item *item);

	t_itemprops			props;
}						t_item;

typedef struct s_fullitem
{
	const char			*name;
	float				font_size;
	int					id;
	int					slot;
	int					effect;
	int					time;
	int					*intvar;
	void				(*use)(t_itemprops);
	void				(*right_click)(t_item *);
}						t_fullitem;

void					init_items(void);
void					init_weapons(t_cube *c);
void					init_potions(t_cube *c);
void					init_armor(t_cube *c);
void					init_keys_items(t_cube *c);

void					instand_death(t_itemprops props);
void					cure(t_itemprops props);
void					equip(t_itemprops props);
void					unequip(void *props);
void					consume(t_itemprops props);

void					use_item(void *arg);
void					item_tooltip(void *arg);
void					place(t_item *item);

t_item					*create_item(const t_fullitem *props);

#endif