/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 09:54:24 by mli               #+#    #+#             */
/*   Updated: 2020/09/28 10:50:56 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/stat.h>

void			exe_root(t_btree *ast, t_control *control);

int				exe_semi(t_btree *ast, t_control *control);
int				exe_and(t_btree *ast, t_control *control);
int				exe_or(t_btree *ast, t_control *control);
int				exe_cmd(t_btree *ast, t_control *control);
int				exe_subshell(t_btree *ast, t_control *control);
int				exe_pipe(t_btree *ast, t_control *control);
void			exe_pipe_child(t_btree *ast, t_control *control);

int				exe_binary(t_simple_cmd *cmd, t_control *control);
int				exe_binary_fork(char *prog, char **argv, t_control *control);
int				exe_given_path(char **argv0, t_control *control, char **path);
int				exe_search_path(char *argv0, t_control *control, char **path);
char			**build_env2d(t_list *env, t_control *control);

int				exe_is_builtin(char *argv0);
int				exe_call_builtin(t_simple_cmd *cmd, int id, \
			t_control *control);

int				exe_simple_cmd_root(t_token *token, t_control *control);
int				exe_prepare_simple_cmd(t_token *token, t_control *control);

int				exe_perform_arrow(t_simple_cmd *cmd, t_control *control);
int				exe_perform_redirections(t_arrow *arrow, t_control *control);
int				exe_perform_indirections(t_arrow *arrow, t_control *control);
int				exe_cancel_arrows(t_control *control);

int				list_to_cmd_root(t_token *token_node);
t_list			*list_to_cmd_skim_redirections(t_list **tokens);
int				list_to_cmd_fill_argv_array(t_simple_cmd *cmd, t_list *tokens);
t_simple_cmd	*init_t_simple_cmd(void);
void			free_t_simple_cmd(void *void_cmd);

int				list_to_cmd_fill_redirections_fields(t_simple_cmd *cmd, \
			t_list *tokens);
int				list_to_cmd_fill_redirections_fields2(t_simple_cmd *cmd, \
			int id, t_list *tokens);
t_arrow			*init_t_arrow(void);
void			free_t_arrow(void *void_arrow);

int				word_expand_root(t_list **tokens, t_control *control);
int				word_expand_and_replace(t_list ***tokens, t_control *control);
int				word_expand_stage1(t_list **tokens, t_control *control);
void			word_expand_replace(t_list ***tokens, t_list *expanded);
t_list			*dup_token(const t_token *token);

void			skim_empty_tokens(t_list **tokens);

int				parameter_expansion_root(t_list *token, t_control *control, \
			int filename);
int				parameter_exp(t_list *token, t_control *ctrl, \
			t_expansion exp, int res);
void			reset_t_expansion(t_expansion *exp, int is_filename, \
			t_control *control);
int				param_exp_find_start(t_list *token, int start, char *quot);
int				param_exp_find_end(t_list *token, int start);
char			*param_exp_get_env(t_control *control, char *str, int len);

int				parameter_expansion2(t_list **token, char **var, \
			t_expansion *exp);
int				need_to_field_split1(char **str, t_expansion *exp);
int				need_to_field_split2(char **str, t_expansion *exp);
int				param_exp_no_fsplit(t_list *token, char *var, \
			t_expansion *exp);

int				field_splitting_root(t_list **token, char *var, \
			t_expansion *exp);
int				field_splitting_root_assist(t_list **token, t_expansion *exp, \
			char *var, char *str2);
int				field_splitting(t_list **token, t_expansion *exp, \
			char **array, char *str2);
int				field_splitting_assist(t_list **tok, char *str);

int				tild_expansion_root(t_list *env, char **str);
int				index_assignement_sign(char *str);
int				tild_expand_try(char **str, char *home_env, int *i);
int				is_tild_expandable(char *str, int i);

int				tild_expand_try_after_column(char **str, char *home_env, \
			int *i);
int				expand_tild_in_assignement(char **str, char *home_env, int i, \
			int start);

int				pathname_expansion_root(t_list **tokens, \
			int is_filename);
int				pathname_is_expandable(char *str);
int				pathname_expansion(t_list ***token, int is_filename);
void			init_path_expansion_struct(t_list *path_parts, \
			t_path_exp *tool, int is_filename);

t_list			*split_path_root(char *path_to_split);
void			collapse_fwd_slashes(char *str, int esc_next, int i, int k);
int				split_path(char *path_to_cut, t_list **path_parts, int i);
int				find_path_end(char *str, int i, char *quoted);
void			path_set_quoted(char c, char *quoted);

int				add_path_part(char *str, t_list **path_parts, char quoted);
t_path_part		*init_path_part_link(char *str, char quoted);
void			delete_path_part_link(void *content);

int				path_part_unquoting(t_path_part *new, char *str);
void			path_part_unquoting_assist(char c, char *quoted, \
		char *str, int *index);
void			path_part_unquoting_escape_char(char *str, int *i, char quoted);
int				add_index_valid_kleen_star_to_lst(t_path_part *new, int index);

int				pathname_matching_root(t_path_exp *tool, t_list *path_parts);
int				pathname_matching_relative(t_path_exp *tool, \
			t_list *path_parts);
int				pathname_matching(t_path_exp *tool, t_list *path_parts, \
			char *path_start, char *open_me);
int				pathname_matching_assist(t_path_exp *tool, t_list *path_parts,\
			char *path_start, char *open_me);
char			*path_join(char *str, char *str2);
int				pathname_matching_closedir_return(DIR *dir_p, int ret);

int				pathname_matched_add_to_list(t_path_exp *tool, char *path);
int				pathname_matching_closedir_return(DIR *dir_p, int ret);

int				match_path_check_valid_star(t_list *wild_cards, int index);
int				match_path_part(t_strings strs, t_list *wild_cards, int i, \
			int j);
int				match_path_part_root(t_list *path_parts, char *ref);

void			quote_removal(t_token *token);
void			quote_removal_unquoted_part(char *str, int i, \
			t_no_unquote *no);
void			quote_removal_doubly_quoted_part(char *str, int i, \
			t_no_unquote *no);
int				quote_removal_skip_protected_part(char *str, int *i, \
			t_no_unquote *no);
int				quote_removal_eat_char(char *str, int *i, t_no_unquote *no);

void			ft_errno_exit(void);

#endif
