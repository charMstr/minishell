#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"

//for the terminfo database. usings the "termcaps" control sequences.
# include <curses.h>
# include <term.h>

//for the termios struct. enables raw mode. manipulates the "line discipline"
# include <termios.h>

# include "structures.h"
# include "lexing.h"
# include "builtin.h"
# include "parser.h"
# include "terminfo.h"

//remove me when done.
# include "debug_terminfo.h"
# include "debug.h"


# define BUFFER_SIZE 32

extern int	errno;


char		*get_next_command(int *quit);
void		child_get_next_command(int fd_w);
char 		*collect_char_by_char(int fd_r);

int			only_white_spaces(char *str);

//minishell_utils
void		ft_pipe(int (*fildes)[2]);
void		ft_fork(int *pid);
void		ft_fork_pipe(t_mysh *mini);
void		ft_perror(char *str, int status);

#endif
