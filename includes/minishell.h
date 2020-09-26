/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 09:52:33 by mli               #+#    #+#             */
/*   Updated: 2020/09/26 20:29:20 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/libft.h"

# include <curses.h>
# include <term.h>

# include <termios.h>

# include "structures.h"

# include "lexing.h"
# include "builtin.h"
# include "parser.h"
# include "terminfo.h"
# include "historic.h"
# include "exe.h"

# define BUFFER_SIZE 32

# define B_ECHO 1
# define B_CD 2
# define B_PWD 3
# define B_EXPORT 4
# define B_UNSET 5
# define B_ENV 6
# define B_EXIT 7

# define SIGCAUGHT 128

extern int	errno;

void		ft_pipe(int (*fildes)[2]);
void		ft_fork(pid_t *pid);
void		ft_fork_pipe(t_pipe *pipe);
void		ft_exit(char *cmd, char *param, char *str, int status);
int			ft_perror(char *cmd, char *param, char *str);
void		ft_ambiguous_redirect(char *str, int fd);

void		ft_sigquit(int sigquit);
void		ft_sigint(int sigquit);
void		ft_signalhandler_enable(void);
void		ft_signalhandler_disable(void);

int			reset_prompt(char **ref_from_env, char **term_ps);
int			reset_prompts(t_list *env, t_term *term);
#endif
