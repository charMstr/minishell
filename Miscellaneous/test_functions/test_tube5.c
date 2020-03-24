#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	pid_t child_pid;

	switch (child_pid = fork())
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			sleep(1);
			printf("this is the CHILD PROCESS\n");
			printf("the pid is:%d and the child_pid is :%d\n", getpid(), child_pid);
			break;
		default:
			printf("this is the PARENT PROCESS\n");
			printf("the pid is:%d and the child_pid is :%d\n", getpid(), child_pid);
			break;
	}
	return (0);
}
