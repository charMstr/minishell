#ifndef DEBUG_FUNCTIONS_H
# define DEBUG_FUNCTIONS_H

void	debug_pars_split_commands(char **array);
void	debug_token_struct(t_token *token);
void	debug_tokens_list(t_list *head);
void	debug_env_list(t_list *lst_head);
void	debug_history_list(t_history *hist);

#endif
