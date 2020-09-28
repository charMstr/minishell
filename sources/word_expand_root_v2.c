/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand_root_v2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 10:25:06 by mli               #+#    #+#             */
/*   Updated: 2020/09/28 10:44:20 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** this is the root file for the expansion of words that are part of a simple
** command. the simple command is a linked list of tokens containing a char*
** originating from the node of type LIST in the AST.
**
** Each char* will be sent to a subfunction separatedly for multiple expansion
** stages.  ** It can produce more than one word (at the stage of field splitting, or at
** the stage of pathname substitution using the kleen star operator).
** Therefor the subfunction will Return a linked list.
** Either the answer is valid and the linked list is inserted in place of the
** initial word. or the answer is not and:
**		1/ malloc failure -> control quit is raised, quit the program
**		2/ the word to expand is a filename and:
**			- field slpitting can occur.
**			- pathname substitution gives more than one result
**			in both case:
**				-> ambiguous redirect error message for this simple command
**
** stages of word expansion:
**
**		1)	parameter expansion
**				example: $PWD -> /home/...
**		2)	field splitting, applied to the parameter expansion, only if
**			unquoted.
**				example:	export hey="one       two"
**							echo $hey --> one two
**							the spaces are removed, expansion got split in two.
**							echo "$hey" --> one      two
**							the spaces arent removed. still one uniq string.
**		note:	portion of the new strings that come from an expansion are
**				marked as protected against late quote removal. every char is
**				to be taken litteraly.
**
**		3)	pathname expansion
**				example: ls -> salut salop salt samy
**						 echo sal* -> salut salop salt
**		note:	it only applies if the '*' is unquoted (unescaped etc).
**				basically it only applies if the function
**				is_pathname_expandable() will return true, otherwise we jump to
**				to step 4.
**				also note that some quote removal is done before
**				this action occurs.
**
**		4)	quote removal (not on the protected strings parts resulting
**				from the parameter expansion). it is only done if no
*/

/*
** note:	this function is the root function for the word_expansion. it loops
**			over the tokens list, and calls a subfunction that will try to
**			expand every token independently(its char*).
**			We basically isolate one token and aplly to it all the expansion
**			stages, creating a separate linked list (multiple tokens can be
**			created during this process). When all the expansions are done,
**			the newly created linked list replaces the initial token, and we
**			can move on to the next token.
**
** note:	the tokens that are redirection operators are skipped, but we know
**			the very next one to be the redirection name: is_filename is set.
**
** input:	the address of a linked list of tokens.
**			control struct, mainly for control->quit
**
** Return:	0, OK
**			1, KO, a messsage like "ambiguous redirect" got displayed
**			2, fatal error, raise control->quit.
*/

int		word_expand_root(t_list **tokens, t_control *control)
{
	int id;
	int res;

	while (*tokens)
	{
		id = tklst_id(*tokens);
		if (id == GREAT || id == DGREAT || id == LESS)
		{
			tokens = &(*tokens)->next;
			((t_token*)(*tokens)->content)->is_filename = 1;
		}
		res = word_expand_and_replace(&tokens, control);
		if (res == 1 || res == 2)
			return (res);
		if (res == 3)
			;
		else
			tokens = &(*tokens)->next;
	}
	return (0);
}

/*
** note:	this function is in charge of calling subfunctions,
**			the first one starts a new list with a duplicated token.
**			the second one will receive the dup and try to complete all the
**			expansions, returning either a linked list, or NULL.
**
**	note:	if not successfull:
**			an error message "ambiguous redirect" is written out with the
**			original char *.
**			or a fatal error can be detected also.
**
**			if succesfull:
**			a linked list is going to be inserted in place of the current token
**
** returN:	0, OK
**			1, ambiguous redirect message is displayed here.
**			2, fatal error.
**			3, token got suppressed as it expands to a nul string. therefor
**				then calling loop should not go to next.
*/

int		word_expand_and_replace(t_list ***tokens, t_control *control)
{
	t_list	*expanded_word;
	int		res;
	t_list 	*del_me;

	if (!(expanded_word = dup_token((**tokens)->content)))
		return (2);
	if ((res = word_expand_stage1(&expanded_word, control)))
	{
		if (res == 1)
			ft_ambiguous_redirect(((t_token *)(**tokens)->content)->str, 2);
		if (res < 3)
			ft_lstclear(&expanded_word, del_token);
		if (res == 3)
		{
			del_me = **tokens;
			**tokens = (**tokens)->next;
			del_token(del_me->content);
			ft_free((void **)&del_me);
		}
		return (res);
	}
	word_expand_replace(tokens, expanded_word);
	return (0);
}

/*
** note:	This function will simply duplicate a token containing an initial
**			word and create a new linked list.
**			It will get modified and grow according to the expansion of the
**			initial word. This process is in place so that we can keep the
**			original word all the way long in the case we need to display an
**			error message with that specific original word, untouched.
**
** RETURN:	linked list with one token, OK
**			NULL, KO
*/

t_list	*dup_token(const t_token *token)
{
	t_list	*new_list;
	t_token	*new_token;

	if (!(new_token = malloc(sizeof(t_token))))
		return (NULL);
	ft_memcpy(new_token, token, sizeof(t_token));
	if (!(new_token->str = ft_strdup(token->str)))
	{
		del_token(new_token);
		return (NULL);
	}
	if (!(new_list = ft_lstnew(new_token)))
	{
		del_token(new_token);
		return (NULL);
	}
	return (new_list);
}

/*
** note:	this function will start with a new linked list that contains a
**			copy of the token containing the word we are expanding.
**			it will apply the successful stages of the word expansion, starting
**			with the parameter expansion.
**
** note:	if the parameter expansion and field splitting is successfull,
**			then we will have to loop over the linked list and apply the next
**			steps (pathname expansion).
**
** note:	at this stage, each time something goes wrong, the complete linked
**			list should be freed and we exit.
**
** note:	if the parameter expansion resulted in an empty filename, ambiguous
**			redirect.
**
** note:	to respect the behavior in which a $var that expands to a null
**			string should be suppressed of the token list (and of the argv
**			list), we skim the token list after the parameter expansion.
**
** returN:	0, OK
**			1, ambiguous redirect message is displayed here.
**			2, fatal error.
**			3, the parameter expansion gave an empty list of tokens after
**				skimmming the tokens containing an empty string.
*/

int		word_expand_stage1(t_list **tokens, t_control *control)
{
	int res;
	int is_filename;

	if (!tild_expansion_root(control->env, \
				&((t_token*)(*tokens)->content)->str))
		return (2);
	is_filename = ((t_token *)((*tokens)->content))->is_filename;
	if ((res = parameter_expansion_root(*tokens, control, is_filename)))
		return (res);
	skim_empty_tokens(tokens);
	if (!*tokens)
		return (3);
	if (is_filename && ft_strlen(((t_token*)(*tokens)->content)->str) == 0)
		return (1);
	res = pathname_expansion_root(tokens, is_filename);
	return (res);
}

/*
** note:	this function is in charge of erasing the current token containing
**			the initial word to be expanded, when the expansion got completed
**			and was successfull. The replacement is done in situ in the linked
**			list.
**
** note:	we use a triple pointer so we also update the adress of the link
**			containing the word we are curently expanding in the main while
**			loop in word_expand_root()
**
** input:	- triple pointer to a specific token in a linked list of token.
**			- linked list to insert right there instead.
*/

void	word_expand_replace(t_list ***tokens, t_list *expanded)
{
	t_list *last;
	t_list *del_me;

	last = ft_lstlast(expanded);
	last->next = (**tokens)->next;
	del_me = **tokens;
	**tokens = expanded;
	*tokens = &last;
	del_token(del_me->content);
	free(del_me);
}
