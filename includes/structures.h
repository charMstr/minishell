#ifndef STRUCTURES_H
# define STRUCTURES_H

/*
** structure for the position of the cursror
*/
typedef struct		s_int_pair
{
	int				x;
	int				y;
}					t_int_pair;

/*
** structure for the clipboard (copy, cut, paste)
** highlight: activated with ctrl_k for visual select mode.
** note: the index start and end are inclusive.
*/
typedef struct		s_clipboard
{
	int				highlight;
	int				start;
	int				end;
	int				swaped_end;
	char			*paste_me;
}					t_clipboard;

/*
** structure that contains dataregardig the terminal, helpful for the termcaps.
** line: the current line we will update after prompt.
*/
typedef struct		s_term
{
	char			*line;
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
	t_clipboard		clipboard;
}					t_term;

/*
** structure that handles the history of commands. modified with up and down
** arrows.
** head: the first link contains the current history string. We append to it
** control->term->line again and again if we have to prompt PS2.
*/
typedef struct		s_history
{
	int				size;
	t_dlist			*head;
	int				max_size;
}					t_history;

typedef struct		s_lexer_end
{
	unsigned int other:1;       // Pour '|', '||', '&&'    => PS2 simple
	unsigned int quote:1;       // Pour '\'' , '\"'        => PS2
	unsigned int backslash:1;   // Pour '\\'               => PS2 + Del '\'
	unsigned int brace:1;       // Pour '(''               => PS2
	unsigned int add_semi:1;    // Pour '(''               => PS2 + Append ';'
	unsigned int unexpected;    // Pour ')', '>>', '>' ... => Génère une erreur
}					t_lexer_end;

/*
** see lexing.h for the defined values of the id.
*/
typedef struct		s_token
{
	char			*str;
	unsigned int	open_quote:1;
	unsigned int	esc_next:1;
	int				id;
}					t_token;

/*
** structure for controling the whole minishell.
*/
typedef struct		s_control
{
	unsigned int	quit:1;
	unsigned int	ctrl_c:1;
	int				exit_status;
	t_history		*history;
	t_term			*term;
	t_list 			*env;
	t_lexer_end		lexer_end;
}					t_control;

/*
** This structure contains everything required by a simple command to be run.
** redirections will need to be operated in the order of the linked list.
** the indirections and redirections bothe contains a linked list of t_arrow*.
**	argv_list will hold temporary the argv words until expansion is done.
*/
typedef struct	s_simple_cmd
{
		t_list	*indirections;
		t_list	*redirections;
		t_list 	*argv_list;
		char	**argv;
}				t_simple_cmd;

/*
** this structure holds filename, and type which can be either GREAT, DGREAT,
** LESS, DLESS.
*/
typedef struct	s_arrow
{
	char	*filename;
	int		id;
}				t_arrow;

/*
** this structure is used in the linked list containing the environement
**	variables.
*/
typedef struct	s_env
{
	char *label;
	char *value;
}				t_env;

/*
** structure assising in the process of parameter expansion and field splitting
** start: the position in the string where the $ is at.
** end:	the index of the last char belonging to the variable.
** quoted: will help us know if the field_splitting will be applied or not.
** ifs: internal field separator. stored here for when it comes to the field
**		splittting part.
*/
typedef struct	s_expansion
{
	int			start;
	int			end;
	char		quoted;
	int			field_splitting;
	char		*ifs;
}				t_expansion;

//unused for now
typedef struct	s_mysh
{
	int	pid;
	int	pipe[2];
	int	stat_loc;
}				t_mysh;

#endif
