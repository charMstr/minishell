/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mli <mli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 21:24:05 by mli               #+#    #+#             */
/*   Updated: 2020/04/13 22:20:43 by mli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		lexer_end(t_list *token_head, t_control *control)
{
	char	c;
	t_token	*last;

	last = (t_token *)(ft_lstlast(token_head)->content);
	c = last->str[ft_strlen(str) - 1];
	if (last->open_quote)
		control->lexer_end.quote = 1;
	else if (c == '\\')
		control->lexer_end.backslash = 1;
	else if (last->id == AND || last->id == PIPE || last->id == OR_IF)
		control->lexer_end.other = 1;
	else if (last->id == LBRACE || last->id == RBRACE || last->id == LESS ||
			last->id == DLESS || last->id == GREAT || last->id == DGREAT)
		control->lexer_end.unexpected = last->id;
	else
		return (1);
	return (0);
}
