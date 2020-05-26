/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 16:34:36 by mli               #+#    #+#             */
/*   Updated: 2020/05/26 12:50:18 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include <stdlib.h>
# include <stdio.h>

typedef struct	s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}				t_btree;

t_btree			*btree_new(void *item);
void			btree_apply_prefix(t_btree *root, void (*applyf)(void *));
void			btree_apply_infix(t_btree *root, void (*applyf)(void *));
void			btree_apply_suffix(t_btree *root, void (*applyf)(void *));

void			btree_add(t_btree **root, t_btree *new,
					int (*cmpf)(void *, void *));
void			*btree_find(t_btree *root, void *data_ref,
					int (*cmpf)(void *, void *));

int				btree_depth(t_btree *root);
int				btree_apply_bfs(t_btree *root,
			int (*applyf)(void *item, int current_level, int is_first_elem));

void			btree_clear(t_btree **node, void (*del)(void *));
void			btree_delone(t_btree **node, void (*del)(void *));

#endif
