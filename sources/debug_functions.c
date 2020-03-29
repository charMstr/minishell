#include "debug.h"

void	debug_pars_split_commands(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		ft_putendl_fd(tab[i], 2);
		i++;
	}
}

void	debug_tokens_list(t_list *head)
{
	while (head)
	{
		ft_putendl_fd("\n=====================\nlink start\n===================", 2);
		debug_token_struct((t_token*)(head->content));
		ft_putendl_fd("=====================\nlink end\n=====================\n\n", 2);
		head = head->next;
	}
}

void	debug_token_struct(t_token *token)
{
	if (!token->str)
	{
		ft_putendl_fd("the token contains an empty string", 2);
		return ;
	}
	ft_putendl_fd("the token contains the string:", 2);
	ft_putendl_fd(token->str, 2);
	ft_putstr_fd("lenght of the string: ", 2);
	ft_putnbr_fd(ft_strlen(token->str), 2);
	ft_putendl_fd("", 2);
}

void	debug_lexing_struct(t_lexing *lex)
{
	ft_putendl_fd("\n---------------------\nlexing start\n-------------------", 2);
	printf("operator: %d\n", lex->operator);
	printf("s_quoted: %d\n", lex->s_quoted);
	printf("d_quoted: %d\n", lex->d_quoted);
	printf("empty: %d\n", lex->empty);
	printf("esc_next: %d\n", lex->esc_next);
	printf("is_alpha: %d\n", lex->is_alpha);
	printf("is_num: %d\n", lex->is_num);
	ft_putendl_fd("-----------------------\nlexing end\n---------------------\n\n", 2);
}
