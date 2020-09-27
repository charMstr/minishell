/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 09:42:58 by mli               #+#    #+#             */
/*   Updated: 2020/09/27 15:13:34 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

t_list	*env_build_linked_list(char **env);
t_env	*env_build(char *str);
void	env_del_struct(void *env);
int		env_builtin(t_list *env, t_control *control);
t_env	*env_init_struct(void);
char	*env_get(char *str, size_t len, t_list *env);
char	**env_get_addr(char *str, size_t len, t_list *env);
int		env_shlvl_update(t_list **env, t_control *control);

int		is_identifier_valid(char *identifier, char *command);

int		unset_builtin(t_list **env_head, char **argv, t_control *control);
void	unset_in_env_list(t_list **env_head, char *str);

int		export_builtin(t_list **head, char **argv, t_control *control);
int		export_builtin2(t_list **head, char **argv, t_control *control);
int		export_builtin_new_env(char *str, char *str2, t_list **head);
char	*export_builtin_check_label(char *str, t_control *control);
void	export_builtin_no_arg(t_list **head, t_control *control);

int		echo_builtin(char **argv, t_control *control);

int		pwd_builtin(t_control *control);

int		cd_builtin(t_list *env, char **argv, t_control *control);
void	ft_ls(char *directory, int showdot);
int		ft_getcwd(char **target);
int		ft_chdir(char *target_dir, t_list *env, t_control *control);
int		cd_special(char *envdir, t_list *env, t_control *control);

int		exit_builtin(char **argv, t_control *control);

#endif
