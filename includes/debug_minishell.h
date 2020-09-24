/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 09:43:05 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 09:44:34 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_MINISHELL_H
# define DEBUG_MINISHELL_H

# include "../libft/libft.h"
# include "minishell.h"

void	debug_pars_split_commands(char **array);
void	debug_token_struct(t_token *token);
void	debug_tokens_list(t_list *head);
void	debug_env_list(t_list *lst_head);
void	debug_history_list(t_history *hist);
void	debug_lexer_flags(t_control *control);

/*
** exe functions.
*/

void	debug_simple_cmd(t_simple_cmd *cmd);
void	debug_node_id(t_btree *node);
void	debug_arrow_struct(t_arrow *arrow);
void	debug_array(char **array);
void	debug_unquote(t_token *token);
void	debug_path_part(t_path_part *path_part);

# define SIZE_LEAF 6

void	btree_debug(t_btree *root, void (*display)());

#endif
