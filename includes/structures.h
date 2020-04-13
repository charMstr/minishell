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
	int				prompt_ps1;
	char			*ps1;
	char			*ps2;
	int				prompt_len;
	char			**array_esc_seq;
	t_dlist			*current_history_link;
}					t_term;

typedef struct		s_history
{
	int				size;
	t_dlist			*head; //the first link contains the current history string
	//we append to it control->term->line again and again if we have to prompt PS2
	int				max_size;
}					t_history;

typedef struct		s_lexer_end
{
	unsigned int other:1;       // Pour '|', '||', '&&'       => PS2 simple
	unsigned int quote:1;       // Pour '\'' , '\"'           => PS2
	unsigned int backslash:1;   // Pour '/'                   => PS2 + Il faudra supprimer le '\'
	unsigned int unexpected;    // Pour '(', ')'  +autre?     => Génère une erreur, avec le char en question dedans
}					t_lexer_end;

typedef struct		s_token
{
	char			*str;
	unsigned int	open_quote:1;
	unsigned int	esc_next:1;
	int				id;
}					t_token;

//structure for controling the whole minishell.
typedef struct		s_control
{
	unsigned int	quit:1;
	unsigned int	ctrl_c:1;
	int				exit_status;
	t_history		*history;
	t_term			*term;
	t_lexer_end		lexer_end;
}					t_control;

typedef struct	s_mysh
{
	int	pid;
	int	pipe[2];
	int	stat_loc;
}				t_mysh;

#endif
