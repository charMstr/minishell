#include "minishell.h"

void	debug_node_id(t_btree *node)
{
	printf("\033[35mnode id:");
	if (!node)
		printf("\033[31mnode is NULL:\n");
	else if (btree_id(node) == TOKEN)
		printf("TOKEN\n");
	else if (btree_id(node) == SEMI)
		printf("SEMI\n");
	else if (btree_id(node) == PIPE)
		printf("PIPE\n");
	else if (btree_id(node) == OR_IF)
		printf("OR_IF\n");
	else if (btree_id(node) == AND)
		printf("AND\n");
	else if (btree_id(node) == AND_IF)
		printf("AND_IF\n");
	else if (btree_id(node) == LBRACE)
		printf("LBRACE\n");
	else if (btree_id(node) == RBRACE)
		printf("RBRACE\n");
	else if (btree_id(node) == S_QUOTE)
		printf("S_QUOTE\n");
	else if (btree_id(node) == D_QUOTE)
		printf("D_QUOTE\n");
	else if (btree_id(node) == LESS)
		printf("LESS\n");
	else if (btree_id(node) == DLESS)
		printf("DLESS\n");
	else if (btree_id(node) == GREAT)
		printf("GREAT\n");
	else if (btree_id(node) == DGREAT)
		printf("DGREAT\n");
	else if (btree_id(node) == SUBSHELL)
		printf("SUBSHELL\n");
	else if (btree_id(node) == LIST)
		printf("LIST\n");
	else
		printf("\033[31mWARNING, id unrecognized\n");
	printf("\033[0m");
}

void	debug_arrow_struct(t_arrow *arrow)
{
	if (!arrow)
	{
		printf("\033[31mWARNING, the arrow pointer was null.\n\033[0m");
		return ;
	}
	printf("\tarrow->id = ");
	if (arrow->id == GREAT)
		printf("GREAT\n");
	else if (arrow->id == DGREAT)
		printf("DGREAT\n");
	else if (arrow->id == LESS)
		printf("LESS\n");
	else
		printf("\033[31mWR0NG ID\033[0m\n");
	printf("\tarrow->dest = [%s]\n", arrow->dest);
}

void	debug_simple_cmd(t_simple_cmd *cmd)
{
	int i;
	t_list *tmp;

	i = 0;
	printf("\n==============================================================\n");
	printf("=============================== DEBUG SIMPLE_CMD =============\n");
	if (!cmd)
	{
		printf("\033[31mWARNING, the cmd structure is a NULL pointer\n\033[0m");
		return ;
	}
	printf("argv:\n");
	if (!cmd->argv)
	{
		printf("\033[31mWARNING, the cmd->argv is a NULL pointer\n\033[0m");
	}
	while (cmd->argv && cmd->argv[i])
	{
		printf("\tcmd->argv[%d]: [%s]\n", i, cmd->argv[i]);
		i++;
	}
	printf("arrows:\n");
	tmp = cmd->arrows;
	while (tmp)
	{
		debug_arrow_struct((t_arrow*)tmp->content);
		tmp = tmp->next;
	}
	printf("======================= END DEBUG SIMPLE_CMD =================\n");
}

void	debug_array(char **array)
{
	int i;

	i = 0;
	printf("\n==============================================================\n");
	printf("=============================== DEBUG ARRAY ==================\n");
	if (!array || !*array)
	{
		printf("\033[31mNULL POINTER!\033[0m\n");
		return ;
	}
	while (array[i])
	{
		printf("\t[%s]\n", array[i]);
		i++;
	}
	printf("======================= END DEBUG ARRAY ======================\n");
}

void	debug_unquote(t_token *token)
{
	printf("\n==============================================================\n");
	printf("=============================== DEBUG UNQUOTE ================\n");
	printf("the string is: [%s]\n", token->str);
	if (!token->unquote_protected)
	{
		printf("\033[31mthe protection is off\033[0m\n");
		return ;
	}
	printf("\033[32mthe protection is ON\033[0m\n");
	printf("start: %d\n", token->protect_s);
	printf("end: %d\n", token->protect_e);
	printf("======================= END DEBUG UNQUOTE ====================\n");
}

void	debug_path_parts(t_list *path_parts)
{
	int i;

	i = 0;
	printf("\n==============================================================\n");
	printf("============================= DEBUG PATH_PARTS ===============\n");
	while (path_parts)
	{
		printf("[%d] str is: [%s]\n", i++, ((t_path_part *)(path_parts->content))->path_part);
		path_parts = path_parts->next;
	}
	printf("==================== END DEBUG PATH_PARTS ====================\n");
}

void	debug_path_part(t_path_part *path_part)
{
	t_list *stars;

	printf("\n==============================================================\n");
	printf("============================= DEBUG PATH_PART ================\n");
	printf("the string is: [%s]\n", path_part->path_part);
	printf("quoted at the start of the string was: %d\n", path_part->quoted);
	printf("the ints linked list:\n");

	stars = path_part->star_index;
	while (stars)
	{
		printf("valid star a index: [%d]\n", *((int*)stars->content));
		stars = stars->next;
	}
	printf("===================== END DEBUG PATH_PART ====================\n");
}
