#include "minishell.h"

/*
** note:	this function will be called when we met an ast tree node, that is
**			a token with id LIST. It therefore contains in its str field, not a
**			string but a linked list of t_tokens* which are the WORDS and
**			REDIRECTIONS operators of a simple command to be executed.
**
** note:	once the words are expanded, we can modify token->str from being a
**			t_list * of tokens to a structure containing:
**			argv, and two linked lists for the redirections.
**			we also change the current token's id from LIST to CMD.
**
** note:	the the execution can be done. first the redirections are operated
**			then we try to execute a builin, then a binary.
**
** note:	control->quit will be raised in case of failure in mallocs
**			exit_status should alway be set here.
**
** RETURN:	1 OK
**			0 KO
*/

int	exe_simple_cmd_root(t_token *token, t_control *control)
{
	int builtin;
//	printf("\033[34mBEFORE WORD EXPAND:\033[0m\n");
//	debug_tokens_list((t_list *)token->str);
	if (!word_expand_root((t_list *)token->str, control))
	{
		control->quit = 1;
		return (0);
	}
//	printf("\033[34mAFTER WORD EXPAND:\033[0m\n");
//	debug_tokens_list((t_list *)token->str);
	if (!list_to_cmd_root(token))
	{
		control->quit = 1;
		return (0);
	}
	debug_simple_cmd(((t_simple_cmd *)token->str));
	//HERE command to does all the redirections.
	//need to operate the redirections list just before executing the simple
	//command. note: the stdin and stdout, should be
	if ((builtin = exe_is_builtin(((t_simple_cmd *)token->str)->argv[0])))
	{
		printf("\033[35mthis is a builtin\033[0m\n");
		exe_call_builtin(((t_simple_cmd *)token->str), builtin, control);
	}
	//try execute the non builtin commands here.
	//always make sure we set the exit status.
	return (1);
}

/*
** note:	This function is in charge of calling the right builtin.
** note:	Failure can occure because some builin like set use malloc.
** input:	id is the builin id, see typedef in .h
**			control struct
**
** RETURN:	1 OK
**			0 KO.
*/

void	exe_call_builtin(t_simple_cmd *cmd, int id, t_control *control)
{
	if (id == B_ECHO)
		echo_builtin(cmd->argv);
	else if (id == B_ENV)
		env_builtin(control->env);
	else if (id == B_EXPORT)
		export_builtin(&control->env, cmd->argv);
	else if (id == B_UNSET)
		unset_builtin(&control->env, cmd->argv);
}

/*
** note:	this function will have to tell us if the command to run is a
**			builtin or not.
**
** return:	builtin number
**			0 other.
*/

int	exe_is_builtin(char *argv0) //OK
{
	if (!argv0)
		return (0);
	if (!ft_strcmp(argv0, "echo"))
		return (B_ECHO);
	else if (!ft_strcmp(argv0, "cd"))
		return (B_CD);
	else if (!ft_strcmp(argv0, "pwd"))
		return (B_PWD);
	else if (!ft_strcmp(argv0, "export"))
		return (B_EXPORT);
	else if (!ft_strcmp(argv0, "unset"))
		return (B_UNSET);
	else if (!ft_strcmp(argv0, "env"))
		return (B_ENV);
	else if (!ft_strcmp(argv0, "exit"))
		return (B_EXIT);
	else
		return (0);
}
