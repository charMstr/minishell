/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_end2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 19:23:03 by mli               #+#    #+#             */
/*   Updated: 2020/05/17 19:17:34 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer_tk_id_chr(const int *nb, t_token *target)
{
	if (lexer_id_cmp(target, (int *)nb) == 0)
		return (1);
	return (0);
}

int		lexer_tk_notbeside(t_token *curr, t_token *next, int *forbid, int self)
{
	if ((self && next->id == curr->id) ||
		(forbid && lexer_tk_id_chr(forbid, next)))
		return (0);
	return (1);
}

int		lexer_forbidden_start_no_exceptions(t_list *token)
{
	t_token *curr_tk;
	t_token *next_tk;

	curr_tk = token->content;
	next_tk = (token->next ? token->next->content : NULL);
	if (next_tk && curr_tk->id == SEMI && next_tk->id == RBRACE)
		return (0);
	return (1);
}

int		lexer_forbidden_start(t_list *tk_head)
{
	const int	*is_start = (int []){SEMI, LBRACE, PIPE, OR_IF, AND, AND_IF,
		-1};
	const int	*forbidden = (int []){SEMI, PIPE, OR_IF, AND, AND_IF, RBRACE,
		-1};

	if (lexer_tk_id_chr(forbidden, tk_head->content))
		return (((t_token *)tk_head->content)->id);
	while (tk_head)
	{
		if (lexer_forbidden_start_no_exceptions(tk_head))
			if (tk_head->next && lexer_tk_id_chr(is_start, tk_head->content) &&
					lexer_tk_id_chr(forbidden, tk_head->next->content))
				return (((t_token *)tk_head->next->content)->id);
		tk_head = tk_head->next;
	}
	return (0);
}

int		lexer_end2(t_list *token_head, t_control *control)
{
	(void)token_head; (void)control;


	return (0);
}
