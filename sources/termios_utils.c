#include "minishell.h"

/*
** note:	this function will initialise the line discipline of the terminal
**			through the struct termios.
** note:	this function saves in old pointer the previous settings.
**
** RETURN:	0 if faillure
**			1 OK
*/

int	termios_enable_raw_mode(struct termios *old)
{
	struct termios new;

	new = *old;
	//This would turn off the fact that carriage return (ENTER, 13, '\r') are
	// translated into newline (10, '\n'). we dont want that.
	// old.c_iflag &= ~(ICRNL);

	//Similarly, It turns out that the terminal does a similar translation on
	// the output side. It translates each newline ("\n") we print into a
	// carriage return followed by a newline ("\r\n"). we dont need that.
	//old.c_oflag &= ~(OPOST);

	//disable the software flow control (not really used but ok to do it.)
	new.c_iflag &= ~(IXON);

	//disable the the fact that characters are echo back to the screen
	new.c_lflag &= ~(ECHO);

	//this flag is the one repsonsible for printing ^C or ^D when ISIG has not
	//been disabled yet.
	new.c_lflag &= ~(ECHOCTL);

	//read doesnt wait for a ENTER to be pressed anymore. read char by char
	new.c_lflag &= ~(ICANON);

	//disable the signals like SIGINT or SIGQUIT
	// note: as soon as we come out of this read_line process. we shoud restore
	//the SIGNALS so that ctrl_C  and ctrl_\ will be caught by our processes...
	new.c_lflag &= ~(ISIG);

	//needed to differenciate an escape sequence sent by a key like UP arrow
	//, thus staring by the esc value 27, from the "esc" key its self, 27 as
	// well. we differenciate them because of the timing.
	// if you type on your keyboard the keys "esc" + '[' + 'A' if becomes the
	// up arrow!!!
	new.c_cc[VTIME] = 1;
	new.c_cc[VMIN] = 0;
	//finally apply all the changes
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new) == -1)
		return (0);
	return (1);
}

void	termios_reset_cooked_mode(struct termios *saved_copy)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, saved_copy) == -1)
		ft_exit("tcsetattr can't reset", NULL, strerror(errno), 1);
}
