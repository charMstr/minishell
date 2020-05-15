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

# define SIZE_LEAF 6
void	btree_debug(t_btree *root, void (*display)());


#endif
