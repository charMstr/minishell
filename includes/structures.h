#ifndef STRUCTURES_H
# define STRUCTURES_H

//structure for the position of the cursror
typedef struct		s_int_pair
{
	int				x;
	int				y;
}					t_int_pair;

//structure that contains date regardig the terminal, helpful for the termcaps.
typedef struct		s_term
{
	char			*line; //the curent line we will update after a prompt.
	int				line_len;
	int				inline_position;
	t_int_pair		cursor;
	t_int_pair		cursor_saved;  //unused for now...
	t_int_pair		size_window;
	char			*ps1;
	char			*ps2;
	int				prompt_len;
	char			**array_esc_seq;
}					t_term;

//structure for controling the whole minishell.
typedef struct		s_control
{
	unsigned int	multiline:1;
	unsigned int	first_time:1;
	unsigned int	quit:1;
	unsigned int	ctrl_c:1;
	int				exit_status;
	int				index_in_history;
	t_term			*term;
}					t_control;
/*
	t_list			*history_list;		//needed in the terminfo functions(to go up and down and copy the current history line)
	int				index_in_history;	//current index in the history list (needed in the terminfo functions)
	char			*current_history_line;

	int				l_brace;
	int				r_brace;
	unsigned int	s_quote:1;
	unsigned int	d_quote:1;
	unsigned int	and_or_endl:1;
	unsigned int	synthax_error:1;	//if synthax error detected;
	char			unexpected_token;	//the one to be displayed if synthax error
	*/

typedef struct	s_mysh
{
	int	pid;
	int	pipe[2];
	int	stat_loc;
}				t_mysh;

#endif
