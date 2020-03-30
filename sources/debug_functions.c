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
	ft_putendl_fd("\n=====================\nlink start\n===================", 2);
	while (head)
	{
		printf("[%s]\n", ((t_token *)(head->content))->str);
		head = head->next;
	}
	ft_putendl_fd("=====================\nlink end\n=====================\n\n", 2);
}

void	debug_token_struct(t_token *token)
{
	ft_putendl_fd("\n---------------------\ntoken start\n-------------------", 2);
	printf("string:		[%s]\n", token->str);
	if (token->str)
		printf("lenght:		%zu\n", ft_strlen(token->str));
	printf("ID:   		%d\n", token->id);
	printf("esc_next:	%d\n", token->esc_next);
	printf("open_quote:	%d\n", token->open_quote);
	ft_putendl_fd("-----------------------\ntoken end\n---------------------\n\n", 2);
}
