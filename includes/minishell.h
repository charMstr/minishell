#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include "../libft/libft.h"

//for the terminfo database. usings the "termcaps" control sequences.
# include <curses.h>
# include <term.h>

//for the termios struct. enables raw mode. manipulates the "line discipline"
# include <termios.h>

# include "structures.h"

//remove me when done.
# include "debug_terminfo.h"
# include "debug_minishell.h"

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

extern int	errno;

//minishell_utils
void		ft_pipe(int (*fildes)[2]);
void		ft_fork(int *pid);
void		ft_fork_pipe(t_mysh *mini);
void		ft_perror(char *str, int status);

#endif
