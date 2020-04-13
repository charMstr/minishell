#include "minishell.h"

/*
** this file contains the modified linked list functions.
*/

/*
** note: next = NULL, previous = NULL, content = the argument
** note: if content is NULL it doesnt mather it is still created as is.
**
** RETURN:	new link that was malloced
**			NULL pointer if failure
*/

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist *new;

	if (!(new = (t_dlist *)malloc(sizeof(*new))))
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

/*
** input:	- arg1: head of list, (ex: &head)
**			- arg2: new link to be added
**
** note2:	if *alst is NULL, it means the list was empty. new list is created
*/

void	ft_dlstadd_back(t_dlist **alst, t_dlist *new)
{
	t_dlist *tmp;
	t_dlist *previous;

	if (!alst || !new)
		return ;
	if (!(*alst))
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
	{
		previous = tmp;
		tmp = tmp->next;
	}
	tmp->next = new;
	new->previous = tmp;
}

/*
** input:	- arg1: head of list (ex: &head)
**			- arg2: new link to be added
**
** note2:	if *alst is NULL, it means the list was empty. new list is created
*/

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new)
{
	if (!alst || !new)
		return ;
	if (*alst)
	{
		(*alst)->previous = new;
		new->next = *alst;
	}
	*alst = new;
}

/*
** RETURN:	pointer to very last link
**			NULL if the head of list pointer was NULL
*/

t_dlist	*ft_dlstlast(t_dlist *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

/*
** RETURN:	pointer to very first link
**			NULL if the head of list pointer was NULL
*/

t_dlist	*ft_dlstfirst(t_dlist *lst)
{
	if (lst)
		while (lst->previous)
			lst = lst->previous;
	return (lst);
}

/*
** note:	deletes element and all following ones: different from ft_lstdelone
**
** note:	if you want to delete from the middle of the list:
**			it will go up and down the stream (using previous and next).
*/

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*current;
	t_dlist	*then;

	if (!lst || !del)
		return ;
	if (*lst)
	{
		current = (*lst)->next;
		while (current)
		{
			then = current->next;
			ft_dlstdelone(current, del);
			current = then;
		}
	}
	current = *lst;
	while (current)
	{
		then = current->previous;
		ft_dlstdelone(current, del);
		current = then;
	}
	*lst = NULL;
}

/*
** note:	if we want to extract a link that is in the middle of a list,
**			reconnecting the previous and the following link should be done
**			before calling this function, therefore content->next and
**			content->previous are never freed.
**
** note:	the (*del) function shoud be written specific to content
*/

void	ft_dlstdelone(t_dlist *lst, void (*del)(void *))
{
	if (lst)
	{
		if (del)
			del(lst->content);
		free(lst);
	}
}

/*
** note:	this function will delete the last link of the double linked list.
**			see ft_dlstpop_front as well.
*/

void	ft_dlstpop_back(t_dlist **head, void (*del)(void*))
{
	t_dlist **current;
	t_dlist *then;

	if (!head || !del || !*head)
		return ;
	current = head;
	while (*current)
	{

		then = (*current)->next;
		if (!then)
		{
			ft_dlstdelone(*current, del);
			*current = NULL;
			return ;
		}
		current = &(*current)->next;
	}
}

/*
** note:	this function will delete the front link of the double linked list.
**			see ft_dlstpop_back as well.
*/

void	ft_dlstpop_front(t_dlist **head, void (*del)(void*))
{
	t_dlist *new_head;

	if (!head || !del || !*head)
		return ;
	new_head = (*head)->next;
	ft_dlstdelone(*head, del);
	*head = NULL;
	*head = new_head;
}
