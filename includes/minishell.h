#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"

//remove me when done.
# include "debug.h"

# define BUFFER_SIZE 32

extern int	errno;

typedef struct	s_mysh
{
	int	pid;
	int	pipe[2];
	int	stat_loc;
}				t_mysh;

char		*get_next_command(int *quit);
void		child_get_next_command(int fd_w);
char 		*collect_char_by_char(int fd_r);

void		process_commands(char *line);
int			run_separated_commands(char **tab);

//minishell_utils
void		ft_pipe(int (*fildes)[2]);
void		ft_fork(int *pid);
void		ft_fork_pipe(t_mysh *mini);
void		ft_perror(char *str, int status);
int			len_2d(char **tab);

//parsing
int			pars_no_multiline(char *line);
int			ft_strichr_esc(const char *str, char c);

char		**pars_split_commands(char *line, char c);
int			pars_count_cmds(char *line, char c);
int			pars_jump_quoted_section(char *line);
char		*pars_get_next_cmd_word(char *line, int *index, char c);

int			pars_separated_runs_array(char **tab);
int			pars_separated_runs_string(char *str, int very_last);
void		pars_unexpected_token(char *token);


#endif
