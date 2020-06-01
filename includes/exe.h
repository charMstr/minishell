#ifndef EXE_H
# define EXE_H

# include "minishell.h"

void			exe_root(t_btree *ast, t_control *control);
int				exe_is_builtin(char *argv0);
int				exe_prototype(t_control *control, t_btree *ast);
void			exe_call_builtin(t_simple_cmd *cmd, int id, \
			t_control *control);

int				exe_simple_cmd_root(t_token *token, t_control *control);

int				list_to_cmd_root(t_token *token_node);
t_list			*list_to_cmd_skim_redirections(t_list **tokens);
int				list_to_cmd_fill_argv_array(t_simple_cmd *cmd, t_list *tokens);
t_simple_cmd	*init_t_simple_cmd(void);
void			free_t_simple_cmd(void *void_cmd);

int				list_to_cmd_fill_redirections_fields(t_simple_cmd *cmd, \
			t_list *tokens);
int				list_to_cmd_fill_redirections_fields2(t_simple_cmd *cmd, \
			int id, char **str);
t_arrow			*init_t_arrow(void);
void			free_t_arrow(void *void_arrow);

int				word_expand_root(t_list *tokens, t_control *control);
int				parameter_expansion_loop(t_list **tokens, t_control *control);
void			quote_removal_loop(t_list **tokens);

int				parameter_expansion(t_list **token, t_control *control, \
			int field_split);
int				param_exp_find_start(t_list **token, int start, char *quot);
int				param_exp_find_end(t_list **token, int start);
char			*param_exp_get_env(t_control *control, char *str, int len);
void			reset_t_expanssion(t_expansion *exp, int field_splitting);

int				param_exp2(t_list ***token, t_control *control, char *var, \
			t_expansion *exp);
int				param_exp_field_split(t_list ***token, t_expansion *exp, \
			char *var, char *str2);
int				param_exp_no_fsplit(char **str, char *var, char *str2, \
			t_expansion *exp);
int				param_exp_field_split2(t_list **token, t_expansion *exp, \
			char **array, char *str2);
char			**param_exp2_assist(t_expansion *x, t_list *token, \
			t_control *control);

int				field_splitting(t_list ***token, t_expansion *exp, \
			char **array, char *str2);
int				field_splitting_assist(t_list **tok, char *str);

void			quote_removal(t_token *token);
void			quote_removal_unquoted_part(char *str, int i, \
			t_no_unquote *no);
void			quote_removal_doubly_quoted_part(char *str, int i, \
			t_no_unquote *no);
int				quote_removal_skip_protected_part(char *str, int *i, \
			t_no_unquote *no);
int				quote_removal_eat_char(char *str, int *i, t_no_unquote *no);

int				pathname_expand_root(char *str);

int				match_star(char *str, char *star, int quoted, int offset);
void			match_within_quote_escape_met(int *j, char *str, \
			int *esc_next);
int				match_no_star(char *ref, char *no_star, int esc_next, int j);
int				match_until_double_quote(char *ref, char *str, int esc_next);
int				match_within_quote(char *ref, char *str, char quote);

#endif
