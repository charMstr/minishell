#include "debug.h"

void	debug_pars_split_commands(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		ft_putendl_fd(array[i], 2);
		i++;
	}
}

void	debug_tokens_list(t_list *head)
{
	int i;

	ft_putendl_fd("\n=====================\ntokens list start\n===================", 2);
	while (head)
	{
		i =  ((t_token *)(head->content))->id;
		printf("[%s]", ((t_token *)(head->content))->str);
		if (i == TOKEN)
			printf("(TOKEN)\n");
		else if (i == SEMI)
			printf("(SEMI)\n");
		else if (i == PIPE)
			printf("(PIPE)\n");
		else if (i == OR_IF)
			printf("(OR_IF)\n");
		else if (i == AND)
			printf("(AND)\n");
		else if (i == AND_IF)
			printf("(AND_IF)\n");
		else if (i == LBRACE)
			printf("(LBRACE)\n");
		else if (i == RBRACE)
			printf("(RBRACE)\n");
		else if (i == S_QUOTE)
			printf("(S_QUOTE)\n");
		else if (i == D_QUOTE)
			printf("(D_QUOTE)\n");
		else if (i == LESS)
			printf("(LESS)\n");
		else if (i == DLESS)
			printf("DLESS\n");
		else if (i == GREAT)
			printf("(GREAT)\n");
		else if (i == DGREAT)
			printf("(DGREAT)\n");
		else
			printf("(ERROR warning ASHTUNG)\n");
		head = head->next;
	}
	ft_putendl_fd("=====================\ntokens list end\n=====================\n\n", 2);
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

void	debug_env_list(t_list *head)
{
	while (head)
	{
		printf("--------- new_link:\n");
		printf("label:%s\n",((t_env*)(head->content))->label);
		printf("value:%s\n",((t_env*)(head->content))->value);
		head = head->next;
	}
}
