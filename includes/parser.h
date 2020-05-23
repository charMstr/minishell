#ifndef PARSER_H
# define PARSER_H

/*
** this structure is going to be filed when we meet a redirection operator in
** our token list. the filename will be the first following token.
** note:	the io_number is out of the scope of the minishell subject but if  it
**			is parsed in the t_token structure we can implement it easily if we
**			want...(nop!)
*/

typedef struct	s_io_redirect
{
	char	*filename;	// the first token that follows a redirection operator
	int		type;		// LESS, DLESS, GREAT DGREAT
	int		io_number;	// the n in the formula "[n]> filename"
}				t_io_redirect;


/*
** This structure will contain everything required by a simple command
** according to the shell grammar.
** The cmd_words[0] will be the exact same thing as the cmd_name, the rest will
** be the arguments to the command.
**
** the list_of_redirections list:
** updated each time we find a redirection token (LESS, DLESS, GREAT, DGREAT).
** redirections are parsed from left to right for that same simple command. For
** example if there is > file1 > file2, the last one will erase the previous,
** we will still do a open(file1, O_WRITE | O_TRUNC)... to create file1.
**
*/

typedef struct		s_simple_command
{
	char			*cmd_name;
	char			**cmd_words;
	t_list			*list_of_redirections; // list of t_io_redirect struct
	//a link list of the redirections we will have to operate on every single simple command
}					t_simple_command;


/*
** this will be the structure that contains a job, or "pipe_sequence" according
** to the shell grammar
**
** note:	if we want to do the bonuses with the parenthesis, between the pipe
**			sequence and the simple command, we should have an intermediate
**			structure layer called "command" or more specifically "brace_group"
**			according to shell grammar. BUT we should start easy.
*/

typedef struct		s_pipe_sequence
{
	t_list *simple_command;
}					t_pipe_sequence;

/*
** note:	the name of the type should be "list" according to shell grammar so
**			we call it list_sh because of the libft struct already existing.
** This structure will contain the sequential "and_or" (see shell grammar).
** Basically it will contain the commands separated by a ';'.
**
** note:	If we want to implement bonuses we can add the && and || feature by
**			making an intermediate layer with a "t_and_or" structure. In that
**			structure it would be a linked list of t_pipe_sequence, in which we
**			have a boolean (0 for OR, 1 fro IF) and according to that boolean
**			and the exit status of the preceding t_pipe_sequence we just
**			ran, we would keep processing the t_and_or list elements or not
*/

typedef struct		t_list_sh
{
	t_list			*t_pipe_sequence;
}					t_list_sh;

t_btree				*parser_root(t_list *tokens, t_control *control);

void		del_ast(t_btree **node);
int			token_id(t_token *token);
void		ast_add(t_btree **ast, t_btree *add);
int			parser_cmd(t_list **tklst, t_btree *new);
int			parser_next_child(t_dlist **dlst, t_list **tklst, t_btree **new);
t_btree		*parser_create_ast(t_dlist *dlst, t_list **tklst);

#endif
