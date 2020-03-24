#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


/*
   echo $?
   if the parent tries to write to a closed fd, we get "141"
   if the child tries to write to a close fd, we get "0" because the message
   sent to the shell originates form the parent, not the child!
*/

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	int filedes[2];

	pipe(filedes);
	switch (fork())
	{
		case -1:
			exit(0);
		default:
			close(filedes[0]);
			sleep(1);
			write(filedes[1], "hey", 3);
			exit(0);
			break;
		case 0:
			close(filedes[1]);
			close(filedes[0]);
			break;
	}
	return (0);
}
