#include "minishell.h"

typedef struct		s_tokendb
{
	char	*str;
	int		type;
}					t_tokendb;

char	*debug_id_to_str(int id)
{
	int i = 0;
	t_tokendb *token_type = (t_tokendb []){{"SEMI", SEMI},
	{"LBRACE", LBRACE}, {"RBRACE", RBRACE}, {"PIPE", PIPE}, {"OR_IF", OR_IF},
	{"AND", AND}, {"AND_IF", AND_IF}, {"S_QUOTE", S_QUOTE}, {"D_QUOTE", D_QUOTE},
	{"GREAT", GREAT}, {"DGREAT", DGREAT}, {"LESS", LESS}, {"DLESS", DLESS},
	{"TOKEN", TOKEN}, {"ERROR, NOT RECOGNIZED", -1}};

	while (token_type[i].type != -1 && token_type[i].type != id)
		i++;
	return (token_type[i].str);
}

void	debug_lexer_flags(t_control *control)
{
	printf("[%d]%s\n", control->quit, "Quit");
	printf("[%d]%s\n", control->lexer_end.other, "Other");
	printf("[%d]%s\n", control->lexer_end.quote, "Quote");
	printf("[%d]%s\n", control->lexer_end.backslash, "Backslash");
	printf("[%d]%s\n", control->lexer_end.unexpected, "Unexpected");
}

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
	ft_putendl_fd("\n=================\nTOKENS LIST START\n=================", 2);
	while (head)
	{
		printf("[%s]", ((t_token *)(head->content))->str);
		printf("(%s)\n", debug_id_to_str(((t_token *)head->content)->id));
		head = head->next;
	}
	ft_putendl_fd("=================\nTOKENS LIST END\n=================\n\n", 2);
}

void	debug_token_struct(t_token *token)
{
	ft_putendl_fd("\n---------------------\ntoken start\n-------------------", 2);
	printf("string:		[%s]\n", token->str);
	if (token->str)
		printf("lenght:		%zu\n", ft_strlen(token->str));
	printf("ID:   		%d [%s]\n", token->id, debug_id_to_str(token->id));
	printf("esc_next:	%d\n", token->esc_next);
	printf("open_quote:	%d\n", token->open_quote);
	ft_putendl_fd("---------------------\ntoken end\n---------------------\n", 2);
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

void	debug_history_list(t_history *hist)
{
	int i;
	t_dlist *tmp;

	i = 0;
	if (!hist || !hist->head)
		printf("kunts fucked!!!!\n");
	tmp = hist->head;
	printf("\n==============================================================\n");
	printf("=============================== DEBUG HISTORY ================\n");
	printf("history->size = [%d]\n", hist->size);
	if (tmp)
		printf("head: [%p]\n", tmp);
	while(tmp)
	{
		printf("[%d] -- ADDRESS:[%p] -- STRING:[%s]\n"\
				, i, tmp, (char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
}
