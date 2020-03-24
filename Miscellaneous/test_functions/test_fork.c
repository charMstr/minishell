#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

void	my_handler(int num)
{
	printf("the number of the signal being handled is: %d\n", num);
}

void	display_pipe_ends(int pipe_ends[2])
{
	printf("at index 0 (futur read): %d\n", pipe_ends[0]);
	printf("at index 1 (futur write): %d\n", pipe_ends[1]);
}

int	 child_func(char *message, int pipe_ends[2])
{
	close(pipe_ends[0]);
	close(pipe_ends[1]);
	/*
	close(pipe_ends[0]);
	dup2(pipe_ends[1], STDOUT_FILENO);

	printf("\n===>this is the child process\n" \
			"the pid is :%d\n" \
			"and the ppid is:%d\n", getpid(), getppid());
		display_pipe_ends(pipe_ends);
	//write(pipe_ends[1], message, 30);
	close(pipe_ends[1]);
	*/
	exit(EXIT_SUCCESS);
}

int	parent_func(char *message, int pipe_ends[], int child_pid)
{
	char str[30 + 1];
	int res;

	close(pipe_ends[0]);
	write(pipe_ends[1], message, 30);
	/*
	close(pipe_ends[1]);
	dup2(pipe_ends[0], STDIN_FILENO);

	printf("\n===> this the parent process:\n" \
			"the pid is: %d\n" \
			"and the child pid is: %d\n",getpid(), child_pid);
sleep(1);
	res = read(pipe_ends[0], str, 30);
	str[res] = '\0';
	printf("first read: res = %d\n", res);
	res = read(pipe_ends[0], str, 30);
	str[res] = '\0';
	printf("second readd: res = %d\n", res);
	printf("- read in the parent: |%s|\n", str);
	*/
	printf("in the parent function , did we get there?\n");
	return (0);
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	pid_t pid;
	int	child_ret;

	int pipe_ends[2];
	char message[] = "hey salut!";
	int tmp_stdin;
	int tmp_stdout;

	if (pipe(pipe_ends) == -1)
	{
		perror("pipe function failed\n");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == 0)
	{
		child_func(message, pipe_ends);
	}
	else
	{
		waitpid(pid, &child_ret, WUNTRACED);
		printf("just BEFORE the parent call...\n");
		//nb: as long as the signal handler is declared in the same thread...
		//and as long as it is declared before the signal being produced..
		// then we can catch the signal, even in a different function!
		signal(SIGPIPE, &my_handler);
		parent_func(message, pipe_ends, (int)pid);
		printf("jsut after the parent call...\n");
		display_pipe_ends(pipe_ends);
		if (WIFEXITED(child_ret))
		{
			printf("\n===> the child process exited normally\n");
			printf("the exit status was: %d\n", (int)WEXITSTATUS(child_ret));
		}
	}
	printf("END OF THE MAIN\n");
	return (0);
}
