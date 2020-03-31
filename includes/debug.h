#ifndef DEBUG_H
# define DEBUG_H

# include "../libft/libft.h"
# include "minishell.h"

void	debug_pars_split_commands(char **tab);
void	debug_token_struct(t_token *token);
void	debug_tokens_list(t_list *head);
void	debug_env_list(t_list *lst_head);

#endif
