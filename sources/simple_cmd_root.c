#include "minishell.h"

/*
** note:	This function will parcour the ast in a postorder manner, and
**			recognise if the current tree node is containing the type LIST in
**			its content. If yes it then applies a function to convert the node
**			type into a CMD, Which now contains a t_simple_cmd in its char *str
**			field.
**
** return:	1 OK
**			0 KO
*/

int	simple_cmd_convert_root(t_btree* ast)
{
	int res;

	if (!ast)
		return (1);
	//debug_node_id(ast);
	if ((res = simple_cmd_convert_root(ast->left)))
		res = simple_cmd_convert_root(ast->right);
	if (res && btree_id(ast) == LIST)
		res = simple_cmd_convert1((t_token *)ast->item);
	return (res);
}

/*
** note:	this function calls the subfunction that will convert the token
**			from id LIST to id CMD. and it will unquote the redirections
**
** note:	We dont unquote the argv[1+] yet because the rules are a bit
**			different, especially with the echo builtin that needs to make a
**			distinction between a double quoted, simple quoted and unquoted str
** example:	a command like "cd" is equivalent to cd
**
** RETURN:	1 OK
**			0 KO
*/

int	simple_cmd_convert1(t_token *token_node)
{
	if (!simple_cmd_convert2(token_node))
		return (0);
	simple_cmd_unquote_redirections((t_simple_cmd*)token_node->str);
	unquote_str(((t_simple_cmd*)token_node->str)->argv[0]);
	return (1);
}

/*
** note:	this function will unquote the redirections's filenames in the
**			t_simple_cmd struct's redirections and indirections.
*/

void	simple_cmd_unquote_redirections(t_simple_cmd *cmd)
{
	t_list	*tmp;

	tmp = cmd->redirections;
	while (tmp)
	{
		unquote_str(((t_arrow*)tmp->content)->filename);
		tmp = tmp->next;
	}
	tmp = cmd->indirections;
	while (tmp)
	{
		unquote_str(((t_arrow*)tmp->content)->filename);
		tmp = tmp->next;
	}
}

/*
**	note:	this function will shift all the characters to the left, and
**			replace the last quote by a '\0'. no mallocs.
** note:	the reduce_backslash function is called only if the quote_type is
**			double quote.
*/

void	unquote_str(char *str)
{
	int i;
	char quote_type;

	i = 0;
	if (!str || (str[0] != '\'' && str[0] != '\"'))
		return ;
	if (str[0] == '\'')
		quote_type = '\'';
	else
		quote_type = '\"';
	while (str[i])
	{
		if (quote_type == '\"' && str[i] == '\\' && str[i + 1] == '\\')
			reduce_backslash(str + i);
		i++;
	}
	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		if (!str[i])
			str[i - 1] = '\0';
		i++;
	}
}

/*
** note:	This function is called when removing the quotes from a string
**			if we have a double back_slash, it is reduced to one backslash.
**			Whatever that was on the right is shifted to the left one index
**			magnitude.
*/

void	reduce_backslash(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
}
