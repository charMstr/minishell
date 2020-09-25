/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_simple_cmd_root.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 11:51:13 by mli               #+#    #+#             */
/*   Updated: 2020/09/25 16:18:35 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
**			then we try to execute a builtin, then a binary.
**
** note:	control->quit will be raised in case of failure in mallocs
**			exit_status should alway be set here.
**
** RETURN:	1, OK, process to next command to execute.
**			0, KO, need to exit program.
*/

int	exe_simple_cmd_root(t_token *token, t_control *control)
{
	int builtin;
	int res;

	res = exe_prepare_simple_cmd(token, control);
	if (res == 1)
		return (1);
	//check the exit status is working the same way as the last Return here.
	else if (res == 2)
		return (0);
	//need to make sure the control->quit is raised inside this function..
	if (!exe_perform_arrow((t_simple_cmd *)token->str, control))
	{
		exe_cancel_arrows(control);
		return (0);
	}
	//HERE function that does all the redirections.
	//need to operate the redirections list just before executing the simple
	//command. note: the stdin and stdout, should be saved then restored.
	if (!((t_simple_cmd *)token->str)->argv[0])
		;
	else if ((builtin = exe_is_builtin(((t_simple_cmd *)token->str)->argv[0])))
	{
//		printf("\033[35mthis is a builtin\033[0m\n");
		//check the returned value here;
		exe_call_builtin(((t_simple_cmd *)token->str), builtin, control);
	}
	else
		exe_binary((t_simple_cmd *)token->str, control);
	//try execute the non builtin commands here.
	//always make sure we set the exit status.
	//always restore the stdion and stdout, to original value.
	exe_cancel_arrows(control);
	return (!!control->exit_status);
}

/*
** note:	this function will call the subfunction that operates the word
**			expansions and reassort the tokens into a CMD instead of LIST
**			structure type. (redirections are separated from the basic words).
**
** Return:	0, OK, normal execution
**			1, do not execute this simple command any further, a message like
**			"ambiguous redirect" already got displayed.
**			2, control->quit was raised, need to quit the program.
*/

int	exe_prepare_simple_cmd(t_token *token, t_control *control)
{
	int res;

//	printf("\033[34mBEFORE WORD EXPAND:\033[0m\n");
//	debug_tokens_list((t_list *)token->str);
	res = word_expand_root(((t_list **)&token->str), control);
	if (res)
	{
		control->exit_status = 1;
		if (res == 2)
			control->quit = 1;
		return (res);
	}
//	printf("\033[34mAFTER WORD EXPAND:\033[0m\n");
//	debug_tokens_list((t_list *)token->str);
	if (!list_to_cmd_root(token))
	{
		control->exit_status = 1;
		control->quit = 1;
		return (2);
	}
//	debug_simple_cmd(((t_simple_cmd *)token->str));
	return (0);
}

/*
** note:	This function is in charge of calling the right builtin.
** note:	Failure can occure because some builin like set use malloc.
** input:	id is the builin id, see typedef in .h
**			control struct
**
** RETURN:	1 OK
**			0 KO. it means the control->quit has been raised as well.
*/

int	exe_call_builtin(t_simple_cmd *cmd, int id, t_control *control)
{
	if (id == B_ECHO)
		return (echo_builtin(cmd->argv, control));
	else if (id == B_ENV)
		return (env_builtin(control->env, control));
	else if (id == B_EXPORT)
		return (export_builtin(&control->env, cmd->argv, control));
	else if (id == B_UNSET)
		return (unset_builtin(&control->env, cmd->argv, control));
	else if (id == B_CD)
		return (cd_builtin(control->env, cmd->argv, control));
	else if (id == B_EXIT)
		return (exit_builtin(cmd->argv, control));
	else if (id == B_PWD)
		return (pwd_builtin(control));
	return (0);
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
