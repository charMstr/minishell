#include "minishell.h"

/*
** note:	this function is the root func to inititate the terminfo databse.
**
** RETURN:	NULL if failure
**			pointeur if OK
*/

t_term *terminfo_init_database(void)
{
	int res;
	t_term *term;

	res = setupterm(NULL, STDOUT_FILENO, NULL);
	if (res == ERR) //note: ERR is defined to 1 in the library.
		return (NULL);
	if (!(term = terminfo_init_struct()))
		return (NULL);
	if (!terminfo_load_win_size(term))
		return (terminfo_free_struct(term));
	if (!terminfo_load_array_esc_seq(term))
		return (terminfo_free_struct(term));
	if (!(term->ps1 = ft_strdup("🥑 👌 \033[31mmli_charmstr$ \033[0m")))
		return (terminfo_free_struct(term));
	if (!(term->ps2 = ft_strdup(">")))
		return (terminfo_free_struct(term));
	return (term);
}

/*
** note:	this function is initializing all the files int the t_term
**			struct
** RETURN:	NULL if failure
**			pointer to struct if OK
*/

t_term	*terminfo_init_struct(void)
{
	t_term *term;

	if (!(term = (t_term *)malloc(sizeof(t_term))))
		return (NULL);
	term->line = NULL;
	term->line_len = 0;
	term->inline_position = 0;
	term->array_esc_seq = NULL;
	term->ps1 = NULL;
	term->ps2 = NULL;
	term->prompt_len = 0;
	term->cursor.x = 0;
	term->cursor.y = 0;
	term->cursor_saved.x = 0;
	term->cursor_saved.y = 0;
	term->size_window.x = 0;
	term->size_window.y = 0;
	term->cursor_start.x = 0;
	term->cursor_start.y = 0;
	return (term);
}

/*
** note:	this function is in charge of freeing the struct t_term
**
** RETURN:	NULL always for conveyance.
*/

void 	*terminfo_free_struct(t_term *term)
{
	free(term->line);
	free(term->ps1);
	free(term->ps2);
	ft_array_free(term->array_esc_seq, \
			ft_array_len(term->array_esc_seq));
	free(term);
	return (NULL);
}

/*
** note:	this function will load/reload the dimensions of the terminal
**			window into the term structure.
**
** RETURN:	0 if failure
**			1 OK
*/

int	terminfo_load_win_size(t_term *term)
{
	int res;

	res = tigetnum("cols");
	if (res == -1 || res == -2)
		return (0);
	term->size_window.x = res;
	res = tigetnum("lines");
	if (res == -1 || res == -2)
		return (0);
	term->size_window.y = res;
	return (1);
}

/*
** note:	this function should be called to rest the terminal to default
**			exemple: stop writing in a weird color.
*/

void terminfo_reset_terminal(void)
{
	char *str;

	str = tigetstr("sgr0");
	if (str)
		tputs(str, 1, ft_putchar);
}
