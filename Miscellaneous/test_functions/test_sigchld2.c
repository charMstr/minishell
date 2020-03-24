#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

extern int errno;

void	get_child_status(int sig)
{
	char message[] = "had to stop since the kid stopped\n";
	int pid;
	int stat_loc;

	write(42, message, sizeof(message));
	//ok this is validated, this will abort here the parent process!
	//and this is usefull since once we go into the execve, we cannot add some
	//more lines of code!
	pid = wait(&stat_loc);
	if (WIFEXITED(stat_loc))
	{
		exit(WEXITSTATUS(stat_loc));
	}
	exit(EXIT_FAILURE);
}

void	parent(int fd)
{
	char *argv[] = {"cat", "/dev/random", NULL};

	//before closing the stdout, we do a disgusting clone to 42, just for the
	// sake of the POC
	dup2(STDOUT_FILENO, 42);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execve("/bin/cat", argv, NULL);
	perror("cat");
	exit(EXIT_FAILURE);
}

void	child(int fd)
{
	char *argv[] = {"head", "-1", NULL};

	dup2(fd, STDIN_FILENO);
	close(fd);
	sleep(2);
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

	signal(SIGPIPE, get_child_status);
	switch(fork())
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			//child process (on the right side of the pipe)
			//reset the sigpipe to default for the kid.
			signal(SIGPIPE, SIG_DFL);
			close(tube[1]);
			child(tube[0]);
			break;
		default:
			//parent process  (on the left of the pipe)
			//we will try not to abort when the pipe is broken. but get the
			//childre status instead
			close(tube[0]);
			parent(tube[1]);
			break;
	}
	return (0);
}
