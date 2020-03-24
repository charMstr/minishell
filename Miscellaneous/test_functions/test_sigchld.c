#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

extern int errno;

/* FINDINGS:
   if we want to do the good old cat /dev/random | head -1 and get the result
   0 when we do a echo $?. the only chance is to execute it in a way that the
   child process is on the left side(writting in the pipe).
   As we call the execve() the signal handler we set for the  SIGCHLD is
   completely innefective. when the parent is on the left (writing side of the
   pipe), as the right side finishes (head -1), the left side continues, then
   abort since it tried to write in a pipe that was closed (echo $? => 141).
   and there is nothing we can do about it. except for puting the parent
   process on the right. when the child keeps on writing, it just dies, but on
   on the parent side, we had a ending process.
	note: (double checked. if you try to read from a closed fd, read will just
	returN 0.

	note: if the process on the left fails. it is notified by perror on the
	stderr. but the echo $? still depends on the exit of the most right process
	of the pipe stream!
*/

void	stop_for_kiddo(int sig)
{
	char message[] = "had to stop since the kid stopped\n";
	write(42, message, sizeof(message));
	//ok this is validated, this will abort here the parent process!
	//and this is usefull since once we go into the execve, we cannot add some
	//more lines of code!
	exit(0);
}

void	child(int fd)
{
	char *argv[] = {"cat", "/dev/randomm", NULL};

	//before closing the stdout, we do a disgusting clone to 42, just for the
	// sake of the POC
	dup2(STDOUT_FILENO, 42);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execve("/bin/cat", argv, NULL);
	perror("cat");
	exit(EXIT_FAILURE);
}

void	parent(int fd)
{
	char *argv[] = {"head", "-1", NULL};

	dup2(fd, STDIN_FILENO);
	close(fd);
	//sleep(2);
	execve("/usr/bin/head", argv, NULL);
	perror("execve");
	exit(EXIT_FAILURE);
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	int tube[2];

	if (pipe(tube) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	//note: if we dont put that here, (before the fork()) the signal might
	//never be caught since we are not using wait...
	//signal(SIGCHLD, stop_for_kiddo);

	switch(fork())
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			//child process (on the right side of the pipe)
			close(tube[0]);
			//remove me later...
			//exit(0);
			child(tube[1]);
			break;
		default:
			//parent process  (on the left of the pipe)
			close(tube[1]);
			parent(tube[0]);
			break;
	}
	return (0);
}
