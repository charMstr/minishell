#ifndef BUILTIN_H
# define BUILTIN_H

t_list	*env_build_linked_list(char **env);
t_env	*env_build(char *str);
void	env_del_struct(void *env);
void	env_builtin(t_list *env);
t_env	*env_init_struct(void);
char	*env_get(char *str, size_t len, t_list *env);
char	**env_get_addr(char *str, size_t len, t_list *env);

int		unset_builtin(t_list **env_head, char **argv);
int		unset_in_env_list(t_list **env_head, char *str);

int		export_builtin(t_list **head, char **argv);
int		export_builtin_new_env(char *str, char *str2, t_list **head);
char	*export_builtin_check_label(char *str);

int		echo_builtin(char **argv);

//more than one function for cd?
int		cd_builtin(t_list *env, char **argv);

#endif
