#ifndef EXE_H
# define EXE_H

# include "minishell.h"

void			exe_root(t_btree *ast, t_control *control);
int				exe_is_builtin(char *argv0);
int				exe_prototype(t_control *control, t_btree *ast);
void			exe_call_builtin(t_simple_cmd *cmd, int id, t_control *control);
int				exe_simple_cmd(t_simple_cmd *cmd, t_control *control);


int				cmd_expand_root(t_simple_cmd *cmd, t_control *control);
int				cmd_expand_list_to_argv_array(t_simple_cmd *cmd, \
			t_list *tokens);
int				cmd_expand_argv_token(t_list **argv, t_control *control);
int				word_expand_argv(t_simple_cmd * cmd, t_control *control);
int				parameter_expansion_argv_list(t_list **argv_list, \
			t_control *control);
void			quote_removal_argv_list(t_list **argv_list);

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

#endif
