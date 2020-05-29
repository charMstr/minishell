#include "minishell.h"

/*
** note:	this function is the root function for word expansion, called when
**			we want to execute a simple command.
**
** note:	1)	parameter expansion
**					example: $PWD -> /home/...
**			2)	field splitting (applied to parameter expansion.)
**				example:	export hey="one       two"
**							echo $hey --> one two
**							the spaces are removed, expansion got split in two.
**			3)	pathname expansion
**					example: ls -> salut salop salt samy
**							 echo sal* -> salut salop salt
**			4)	quote removal
**
** note:	the words from the redirections lists will be expanded with more
**			restrictions compared to argv argvs words. they cannot produce more
**			than one word after expansion, so they are not subject to field
**			spliting, the pathname expansion cannot produce more than one word.
**
** note:	control->quit will be raised in case of failure in mallocs
**
** RETURN:	1 OK
**			0 KO
*/

//note: need to set control quit at some stage
int	cmd_expand_root(t_simple_cmd *cmd, t_control *control)
{
	if (!cmd_expand_argv(cmd, control))
	{
		control->quit = 1;
		return (0);
	}
	//cmd_expand_redirections
	//
	return (1);
}

/*
** note:	This function is in charge of the word expansion of the argv list.
**			at the end of the process, the cmd->argv_list is set to null and
 need update
**			all the words expanded are placed in cmd->argv.
**
** RETURN:	1 OK
** 			0 KO
*/

int cmd_expand_argv(t_simple_cmd * cmd, t_control *control)
{
	if (!cmd_expand_argv_list(&cmd->argv_list, control))
		return (0);
	if (!cmd_expand_list_to_argv_array(cmd, cmd->argv_list))
		return (0);
	return (1);
}

/*
** note:	This function is in charge of the word expansion of the argv list.
**			It expands one token at a time. A token can become several tokens,
**			in which case in the subfunction the extra tokens are inserted,
**			and the current *argv_list is updated.
**
** RETURN:	1 OK
** 			0 KO
*/

int cmd_expand_argv_list(t_list **argv_list, t_control *control)
{
	while (*argv_list)
	{
		if (!cmd_expand_argv_token(argv_list, control))
			return (0);
		argv_list = &(*argv_list)->next;
	}
	return (1);
}

/*
** note:	This function expands a single token. Potentially several tokens
**			result from the expansion of one token.
**			if so, the extra token is inserted and the argv is shift to the
**			last added token.
**
** input:	token of type word, we need to expand its str field.
**			t_control struct in which we can found the env list for expansions.
**
//need to add field splitting in the inputs
**
** RETURN:	1 OK
**			0 KO
*/

int	cmd_expand_argv_token(t_list **argv, t_control *control)
{
	//argv->next = NULL;
	if (!(parameter_expansion(argv, control, 1)))
		return (0);
	/*
	if (!field_splitting_root(argv, control, ((t_token *)argv->content)->str))
		return (NULL);
		*/
	//pathname substitution
	//unquoting
	return (1);
}

/*
** note:	this function is called to creat a 2d array and put it into the
**			argv field of the t_simple_cmd struct.
**			the cmd->argv_list is browsed, and one by one the str pointer
**			fields are copied into the array, and then set to NULL.
**
** RETURN:	1 OK
**			0 OK
*/

int	cmd_expand_list_to_argv_array(t_simple_cmd *cmd, t_list *tokens)
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
