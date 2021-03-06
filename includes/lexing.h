/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 09:54:03 by mli               #+#    #+#             */
/*   Updated: 2020/08/21 09:54:19 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

# define TOKEN 0
# define SEMI 1
# define PIPE 2
# define OR_IF 3
# define AND 4
# define AND_IF 5
# define LBRACE 6
# define RBRACE 7
# define S_QUOTE 8
# define D_QUOTE 9
# define LESS 10
# define DLESS 11
# define GREAT 12
# define DGREAT 13

# define SUBSHELL 14
# define LIST 15
# define CMD 16

t_list	*lexer_root(char *input, t_control *control);
t_token	*lexer_build_next_token(const char *input, int *j, t_control *control);
t_token	*lexer_init_token(void);
void	del_token(void *token);

int		lexer_find_token(const char *input, int *j, t_token *token);
int		lexer_jump_esc(int *j, t_token *token);

int		lexer_operator(const char *input, int *j, t_token *token);
int		lexer_operator2(const char *input, int *j, t_token *token);
void	lexer_set_operator_id(t_token *token, char c);

int		lexer_quoted(const char *input, int *j, t_token *token);
int		lexer_quoted_single(const char *input, char c, int *j, t_token *token);
int		lexer_quoted_double(const char *input, char c, int *j, t_token *token);

int		lexer_just_token(const char *input, int *j, t_token *token);
int		lexer_token_or_indirection(const char *input, int *j, t_token *token);
int		lexer_indirection(const char *input, int *j, t_token *token);

int		lexer_id_cmp(t_token *token, int *id);
int		lexer_end(t_list *token_head, t_control *control);

int		lexer_tk_id_chr(const int *nb, t_token *target);
int		lexer_forbidden_start(t_list *tk_head);
int		lexer_forbidden_start_no_exceptions(t_list *token);
int		lexer_tk_notbeside(t_token *curr, t_token *next, int *forbid, int self);
int		lexer_forbidden_combo(t_list *tk_head);

#endif
