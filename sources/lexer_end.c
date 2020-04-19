/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 21:24:05 by mli               #+#    #+#             */
/*   Updated: 2020/04/19 22:57:58 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer_id_cmp(t_token *token, int *id)
{
	while (*id != -1)
	{
		if (token->id == *id)
			return (0);
		id++;
	}
	return (-1);
}

int		lexer_braces_equal(t_list *tk_head, t_control *control, t_token *last)
{
	int		brace[2];

	brace[0] = 0;
	brace[1] = 0;
	while (tk_head && !control->lexer_end.unexpected)
	{
		if (((t_token *)tk_head->content)->id == LBRACE)
			brace[0]++;
		else if (((t_token *)tk_head->content)->id == RBRACE)
			brace[1]++;
		if (brace[0] < brace[1])
			control->lexer_end.unexpected = RBRACE;
		tk_head = tk_head->next;
	}
	if (brace[0] > brace[1])
	{
		control->lexer_end.brace = 1;
		if (last->id != SEMI && last->id != LBRACE)
			control->lexer_end.add_semi = 1;
	}
	else if (brace[0] == brace[1])
		return (1);
	return (0);
}

int 	lexer_signs_near_braces(t_list *tk_head, t_control *control)
{
	t_token		*prev_tk;
	t_token		*curr_tk;
	t_token		*next_tk;
	const int	*signs = (int	[]){LESS, DLESS, GREAT, DGREAT,
		AND, AND_IF, PIPE, OR_IF, SEMI, -1};

	prev_tk = NULL;
	while (tk_head && !control->lexer_end.unexpected)
	{
		curr_tk = (t_token *)tk_head->content;
		next_tk = (tk_head->next ? (t_token *)tk_head->next->content : NULL);
		if ((curr_tk->id == LBRACE && prev_tk) &&
		(lexer_id_cmp(prev_tk, (int *)signs) && prev_tk->id != LBRACE))
			control->lexer_end.unexpected = LBRACE;
		else if ((curr_tk->id == RBRACE && tk_head->next) &&
		(lexer_id_cmp(next_tk, (int *)signs) && next_tk->id != RBRACE))
			control->lexer_end.unexpected = RBRACE;
		else if (curr_tk->id == LBRACE && next_tk &&
			(next_tk->id == RBRACE || next_tk->id == SEMI))
			control->lexer_end.unexpected = next_tk->id;
		prev_tk = (t_token *)tk_head->content;
		tk_head = tk_head->next;
	}
	return (control->lexer_end.unexpected ? 0 : 1);
}

int		lexer_handle_braces(t_list *tk_head, t_control *control, t_token *last)
{
	if (!lexer_signs_near_braces(tk_head, control))
		return (0);
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
	if (((t_token *)token_head->content)->id == SEMI)
		control->lexer_end.unexpected = SEMI;
	else if (last->open_quote)
		control->lexer_end.quote = 1;
	else if (last->esc_next)
		control->lexer_end.backslash = 1;
	else if (last->id == AND_IF || last->id == PIPE || last->id == OR_IF)
		control->lexer_end.other = 1;
	else if (last->id == LESS || last->id == DLESS ||
			last->id == GREAT || last->id == DGREAT)
		control->lexer_end.unexpected = last->id;
	else if (ft_lstfind(token_head, (int	[]){LBRACE, RBRACE, -1},
				lexer_id_cmp))
		return (lexer_handle_braces(token_head, control, last));
	else
		return (1);
	return (0);
}
