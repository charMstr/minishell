#include "minishell.h"
#include <stdio.h>

//color for the debug functions()
void	debug_start(void)
{
	ft_putstr_fd("\033[38;5;123m", 1);
}

void	debug_end(void)
{
	ft_putstr_fd("\033[0m", 1);
}

//diplays the terminal size.

void	debug_term_size(t_term *term)
{
	printf("\n==============================================================\n");
	printf("=============================== DEBUG TERM ===================\n");
	printf("term->size_window.x = %d\n", term->size_window.x);
	printf("term->size_window.y = %d\n", term->size_window.y);
}

//debugs the escacped sequence returned from tigetstr()
void debug_escape_sequence(char *str)
{
        int i = 0;
		int len;

		debug_start();
		if (!str)
		{
			printf("the caps string == NULL\r\n");
			return ;
		}
		len = ft_strlen(str);
		if (!len)
			printf("DEBUG(1/2): the sequence is empty\n");
		else
			printf("DEBUG(1/2): the sequence is [%d] long\n", len);
		ft_putstr_fd("\nDEBUG(2/2): the escape sequence is: \"", 1);
		while (str[i] != '\0')
		{
			if (str[i] == '\x1b')
				ft_putstr_fd("ESC", 1);
			else
				ft_putchar_fd(str[i], 1);
			++i;
		}
		ft_putstr_fd("\"\n", 1);
		debug_end();
}


//debugs the value char we are reading
void debug_value_char(char c)
{
	debug_start();
	if (ft_isprint(c))
		printf("\nDEBUG: the char ['%c'] has the value [%d]\n", c, (int)c);
	else
		printf("\nDEBUG: non printable char has value [%d]\n", (int)c);

	debug_end();
}

//debugs the t_int_pair structure (cursor curent position)
void	debug_cursor(t_int_pair *cursor)
{
	debug_start();
	printf("the coordinates for the current cursor position:\nx: %d\ny: %d\n", \
			cursor->x, cursor->y);
	debug_end();
}

//debugs the term struct
void	debug_term_struct(t_term *term)
{
	debug_start();
	printf("\n\n------------------------------------------------------------");
	printf("\n-------------------------DEBUG FOR THE TERM STRUCT----------\n");
	debug_cursor(&(term->cursor));
	debug_start();
	printf("prompt ps1: [%s]\n", term->ps1);
	debug_start();
	printf("prompt ps2: [%s]\n", term->ps2);
	debug_start();
	printf("length of current prompt: [%d]\n", term->prompt_len);
	debug_start();
	printf("\n-------------------------DEBUG END -------------------------\n");
	debug_start();
	printf("------------------------------------------------------------\n\n");
	debug_end();
}

//debugs the clipboard
void	debug_clipboard_struct(t_clipboard clip)
{
	debug_start();
	printf("\n\n-----------------------------------------------------------\n");
	printf("--------------------- CLIPBOARD DEBUG ----------------------\n");
	printf("highlight: [%d]\n", clip.highlight);
	printf("start: [%d]\n", clip.start);
	printf("end: [%d]\n", clip.end);
	printf("paste_me: [%s]\n", clip.paste_me);
	printf("-----------------------------------------------------------\n");
	debug_end();
}
