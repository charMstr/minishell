/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 09:45:11 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 09:52:03 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*
** this will be the structure that contains a job, or "pipe_sequence" according
** to the shell grammar
**
** note:	if we want to do the bonuses with the parenthesis, between the pipe
**			sequence and the simple command, we should have an intermediate
**			structure layer called "command" or more specifically "brace_group"
**			according to shell grammar. BUT we should start easy.
*/

typedef struct	s_pipe_sequence
{
	t_list		*simple_command;
}				t_pipe_sequence;

/*
** note:	the name of the type should be "list" according to shell grammar so
**			we call it list_sh because of the libft struct already existing.
** This structure will contain the sequential "and_or" (see shell grammar).
** Basically it will contain the commands separated by a ';'.
**
** note:	If we want to implement bonuses we can add the && and || feature by
**			making an intermediate layer with a "t_and_or" structure. In that
**			structure it would be a linked list of t_pipe_sequence, in which we
**			have a boolean (0 for OR, 1 fro IF) and according to that boolean
**			and the exit status of the preceding t_pipe_sequence we just
**			ran, we would keep processing the t_and_or list elements or not
*/

typedef struct	s_list_sh
{
	t_list		*pipe_sequence;
}				t_list_sh;

t_btree			*parser_root(t_list *tokens, t_control *control);

void			del_ast(t_btree **node);
void			ast_add(t_btree **ast, t_btree *add);
int				parser_next_child(t_dlist **lst, t_list **tklst, t_btree **new);
t_btree			*parser_create_ast(t_dlist *dlst, t_list **tklst);

int				parser_cmd_state(t_btree *new, t_list **tklst);
int				parser_is_cmd_param(int tkid);
int				parser_is_cmd_start(int tkid);
int				parser_cmd(t_list **tklst, t_btree **new);

int				token_id(t_token *token);
int				tklst_id(t_list *tklst);
int				btree_id(t_btree *node);
void			parser_disp(t_token *node, t_btree *parent);

#endif
