#ifndef EXE_H
# define EXE_H

# include "minishell.h"

# define B_ECHO 1
# define B_CD 2
# define B_PWD 3
# define B_EXPORT 4
# define B_UNSET 5
# define B_ENV 6
# define B_EXIT 7

void			exe_root(t_btree *ast, t_control *control);

int				simple_cmd_convert_root(t_btree* ast);
int				simple_cmd_convert1(t_token *token_node);
void			simple_cmd_unquote_redirections(t_simple_cmd *cmd);
void			unquote_str(char *str);
void			reduce_backslash(char *str);

int				simple_cmd_convert2(t_token *token_node);
t_simple_cmd	*simple_cmd_init(void);
void			free_simple_cmd_struct(t_simple_cmd *cmd);
t_list			*simple_cmd_skim_redirections(t_list **tokens);
int				simple_cmd_fill_argv_field(t_simple_cmd *cmd, t_list *tokens);

int				simple_cmd_fill_redirections_fields(t_simple_cmd *cmd, \
			t_list *tokens);
int				simple_cmd_fill_redirections_fields_assist(t_simple_cmd *cmd, \
			int id, char **str);
t_arrow			*init_t_arrow(void);
void			free_t_arrow(void *void_arrow);

#endif
