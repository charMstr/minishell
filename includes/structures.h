#ifndef STRUCTURES_H
# define STRUCTURES_H

//structure for the position of the cursror
typedef struct		s_int_pair
{
	int				x;
	int				y;
}					t_int_pair;

//double linked list
typedef struct		s_dlist
{
	void			*content;
	struct s_dlist	*previous;
	struct s_dlist	*next;
}					t_dlist;

//structure that contains date regardig the terminal, helpful for the termcaps.
typedef struct		s_term
{
	char			*line; //the curent line we will update after a prompt.
	int				line_len;
	int				inline_position;
	t_int_pair		cursor;
	t_int_pair		cursor_saved;
	t_int_pair		cursor_start;
	t_int_pair		size_window;
	char			*ps1;
	char			*ps2;
	int				prompt_len;
	char			**array_esc_seq;
	t_dlist			*current_history_link;
}					t_term;

typedef struct		s_history
{
	int				size;
	t_dlist			*head;
	int				max_size;
}					t_history;

//structure for controling the whole minishell.
typedef struct		s_control
{
	unsigned int	multiline:1;
	unsigned int	first_time:1;
	unsigned int	quit:1;
	unsigned int	ctrl_c:1;
	int				exit_status;
	t_history		*history;
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
