#include "minishell.h"

/*
** note:	This function is in charge of the word expansion of the linked list
**			of WORDS originating from the node of type LIST.
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
**			4)	quote removal (not one the protected strings parts resulting
**				from the parameter expansion etc.
**
** note:	During this process, one token can become multiple tokens,
**			(precisely at field splitting and pathname expansion stages), but
**			this never happens for redirections related tokens.
**
** note:	the tokens that are redirection operators are skipped, but we know
**			the very next one to be the redirection name.
**
** RETURN:	1 OK
**			0 KO
*/

int word_expand_root(t_list *tokens, t_control *control)
{
	if (!parameter_expansion_loop(&tokens, control))
		return (0);
	debug_tokens_list(tokens);
	//HERE
	//pathname expansion goes here.
	pathname_expand_root(((t_token *)tokens->content)->str);
	//do a similar loop for the pathname expansion.
	quote_removal_loop(&tokens);
	return (1);
}

/*
** note:	This function is in charge of the parameter expansion list of
**			tokens. it is a subpart of the word expansion process.
**			It expands one token at a time. A token can become several tokens,
**			in which case in the subfunction the extra tokens are inserted,
**			and the current *list is updated.
**
** input:	token of type word, we need to expand its str field and loop.
**			t_control struct in which we can found the env list for expansions.
**
** RETURN:	1 OK
** 			0 KO
*/

int parameter_expansion_loop(t_list **tokens, t_control *control)
{
	int	field_splitting;
	int	id;

	field_splitting = 1;
	while (*tokens)
	{
		id = tklst_id(*tokens);
		if (id == GREAT || id == DGREAT || id == LESS)
		{
			field_splitting = 0;
			tokens = &(*tokens)->next;
		}
		if (!(parameter_expansion(tokens, control, field_splitting)))
			return (0);
		field_splitting = 1;
		tokens = &(*tokens)->next;
	}
	return (1);
}

/*
** note:	this function is in charge of looping over the link list of argv
**			and removing the quotes on each token's string.
**
** input:	token of type word, we need to expand its str field. and loop
*/

void	quote_removal_loop(t_list **tokens)
{
	int id;

	while (*tokens)
	{
		id = tklst_id(*tokens);
		if (id == GREAT || id == DGREAT || id == LESS)
			tokens = &(*tokens)->next;
		quote_removal((t_token*)(*tokens)->content);
		tokens = &(*tokens)->next;
	}
}
