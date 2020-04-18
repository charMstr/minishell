/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 21:24:05 by mli               #+#    #+#             */
/*   Updated: 2020/04/18 22:15:17 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer_find_id(t_token *token, int *id)
{
	if (token->id == *id)
		return (0);
	return (-1);
}

int		lexer_braces_equal(t_list *tk_head, t_control *control, t_token *last)
{
	int		brace[2];

	brace[0] = 0;
	brace[1] = 0;
	while (tk_head)
	{
		if (((t_token *)tk_head->content)->id == LBRACE)
			brace[0]++;
		else if (((t_token *)tk_head->content)->id == RBRACE)
			brace[1]++;
		tk_head = tk_head->next;
	}
	if (brace[0] > brace[1])
	{
		control->lexer_end.brace = 1;
		if (last->id != SEMI)
			control->lexer_end.add_semi = 1;
	}
	else if (brace[0] < brace[1])
		control->lexer_end.unexpected = RBRACE;
	else
		return (1);
	return (0);
}

int		lexer_handle_braces(t_list *tk_head, t_control *control, t_token *last)
{
	if (!lexer_braces_equal(tk_head, control, last))
		return (0);
	return (1);
}

int		lexer_end(t_list *token_head, t_control *control)
{
	t_token	*last;

	if (token_head == NULL || (t_token *)(token_head->content) == NULL)
		return (0);
	last = (t_token *)(ft_lstlast(token_head)->content);
	if (last->open_quote)
		control->lexer_end.quote = 1;
	else if (last->esc_next)
		control->lexer_end.backslash = 1;
	else if (last->id == AND_IF || last->id == PIPE || last->id == OR_IF)
		control->lexer_end.other = 1;
	else if (last->id == LESS || last->id == DLESS ||
			last->id == GREAT || last->id == DGREAT)
		control->lexer_end.unexpected = last->id;
	else if (ft_lstfind(token_head, &(int){LBRACE}, lexer_find_id))
		return (lexer_handle_braces(token_head, control, last));
	else
		return (1);
	return (0);
}
