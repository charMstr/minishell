#ifndef BUILTIN_H
# define BUILTIN_H

t_list	*env_build_linked_list(char **env);
t_env	*env_build(char *str);
void	env_del_struct(void *env);
void	env_builtin(t_list *env);
t_env	*env_init_struct(void);

int		unset_builtin(t_list **env_head, char **argv);
int		unset_in_env_list(t_list **env_head, char *str);

int		export_builtin(t_list **head, char **argv);

int			echo_builtin(char **argv);
#endif
