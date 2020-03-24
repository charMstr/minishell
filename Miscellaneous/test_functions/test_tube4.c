#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

extern int errno;

/*
   exercice ou l'on fait un ls -l | grep toto
*/

void	child(int fd)
{
	char *argv[] = {"ls", "-l", NULL};

	close(STDOUT_FILENO);
	dup(fd);
	close(fd);
	//execve("/bin/ls", argv, NULL);
	//perror("execve");
}


void	parent(int fd)
{
	char *argv[] = {"grep", "toto", NULL};

	close(STDIN_FILENO);
	dup(fd);
	close(fd);
	execve("/usr/bin/grep", argv, NULL);
	perror("execve2");
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	int tube[2];
	pid_t	pid;

	if (pipe(tube) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	switch(pid = fork())
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			close(tube[0]);
			sleep(1);
			child(tube[1]);
			sleep(3);
			break;
		default:
			//wait(&pid);
			close(tube[1]);
			parent(tube[0]);
			break;
	}
	return (0);
}
