#include "minishell.h"

/*
** this file assists the simple_cmd_root.c file.
*/

/*
** note:	this function is called to creat a 2d array with the tokens of type
**			WORD and put it into the argv field of the t_simple_cmd struct
**
** RETURN:	1 OK
**			0 OK
*/

int	simple_cmd_fill_argv_field(t_simple_cmd *cmd, t_list *tokens)
{
	int size;
	int index;
	t_list *copy;

	copy = tokens;
	size = 0;
	index = 0;
	while (copy)
	{
		copy = copy->next;
		size++;
	}
	if (!(cmd->argv = malloc(sizeof(char *) * (size + 1))))
		return (0);
	cmd->argv[size] = NULL;
	while (tokens)
	{
		cmd->argv[index] = ((t_token *)tokens->content)->str;
		((t_token *)tokens->content)->str = NULL;
		tokens = tokens->next;
		index++;
	}
	return (1);
}

/*
** note:	this function is called when we want to build the two linked lists
**			for the redirections and indirections fileds of the t_simple_cmd
**			structure.
**
** input:	a linked list of tokens. each time the first token is a redirection
**			operator and the following one is the name of the file.
**
** RETURN:	0 if malloc failed.
**			1 OK
*/

int	simple_cmd_fill_redirections_fields(t_simple_cmd *cmd, t_list *tokens)
{
	int id;
	while (tokens)
	{
		id = tklst_id(tokens);
		if (id == GREAT || id == DGREAT || id == LESS)
		{
			if (!simple_cmd_fill_redirections_fields_assist(cmd, id, \
						&((t_token *)tokens->next->content)->str))
					return (0);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (1);
}

/*
** note:	this funciton will creat a new t_arrow struct and append it to
**			either cmd->indirection (LESS), or cmd->redirection (GREAT and
**			DGREAT).
**
** input:	the id of the current token, the str of the next token.
** RETURN:	1 OK
** 			0 KO
*/

int	simple_cmd_fill_redirections_fields_assist(t_simple_cmd *cmd, int id, \
		char **str)
{
	t_arrow *arrow;
	t_list *new;

	if (!(arrow = init_t_arrow()))
		return (0);
	arrow->filename = *str;
	*str = NULL;
	arrow->id = id;
	if (!(new = ft_lstnew(arrow)))
	{
		free_t_arrow(arrow);
		return (0);
	}
	if (id == LESS)
		ft_lstadd_back(&cmd->indirections, new);
	else
		ft_lstadd_back(&cmd->redirections, new);
	return (1);
}

/*
** note:	this function creates and bzero a t_arrow pointer.
*/

t_arrow		*init_t_arrow(void)
{
	t_arrow *arrow;

	if (!(arrow = malloc(sizeof(t_arrow))))
		return (NULL);
	ft_bzero(arrow, sizeof(t_arrow));
	return (arrow);
}

void	free_t_arrow(void *void_arrow)
{
	t_arrow *arrow;

	arrow = (t_arrow*)void_arrow;
	free(arrow->filename);
	free(arrow);
}
