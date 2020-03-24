#include "minishell.h"

/*
	note: if try to run acommand that  does not exist (ex: /bin/lsss)
		then errno is set to 2.
*/

extern int errno;

void	child(int fd_w, int option)
{
	char *argv[] = {"cat", "/dev/random", NULL};

	dup2(fd_w, STDOUT_FILENO);
	close(fd_w);
	sleep(1);
	if (option == 1)
		execve("/bin/cat", argv, NULL);
	else if (option == 2)
		execve("/bin/cats", argv, NULL);
	perror("execve");
	printf("%d\n",errno);
	exit(127);
}

void	child_binary(int option)
{
	char *argv[] = {"/usr/bin/head", "-1", NULL};
	char *argv2[] = {"/usr/bin/head", "-=", NULL};

	if (option == 1)
		execve("/usr/bin/head" , argv, NULL);
	else if (option == 3)
		execve("/usr/bin/head", argv2, NULL);
	else if (option == 4)
		execve("/usr/bin/heads", argv, NULL);
	perror("execve (child_binary)");
	printf("%d\n",errno);
	exit(127);
}

void	father(int fd_r, int pid_child, int option )
{
	int pid;
	int	child_ret;

	switch (pid = fork())
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			dup2(fd_r, STDIN_FILENO);
			close(fd_r);
			child_binary(option);
			break;
		default:
			close(fd_r);
			waitpid(pid_child, &child_ret, WUNTRACED);
			printf("we are in the dad and it has finished to wait  for the spawn kid\n");
			printf("child_ret = %d\n", child_ret);
			sleep(2);

			waitpid(pid, &child_ret, WUNTRACED);
			printf("we are in the dad , and it has finished to wait for its binary child\n");
			printf("child_ret = %d\n", child_ret);
			if (WIFEXITED(child_ret))
			{
				printf("\n===> the child process exited normally\n");
				printf("the exit status was: %d\n", (int)WEXITSTATUS(child_ret));
			}
			exit((int)WEXITSTATUS(child_ret));
			break;
	}
}

int	fake_shell(int option)
{
	int fildes[2];
	pid_t pid;

	if (pipe(fildes) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	switch (pid = fork())
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			close(fildes[0]);
			child(fildes[1], option);
			break;
		default:
			close(fildes[1]);
			father(fildes[0], (int)pid, option);
			break;
	}
	return (0);
}

int	fork_subprocesses(int option)
{
	int res;
	pid_t pid;

	switch(pid = fork())
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			fake_shell(option);
			break;
		default:
			waitpid(pid, &res, WUNTRACED);
			if (WIFEXITED(res))
				return ((int)WEXITSTATUS(res));
			break;
	}
	exit(EXIT_FAILURE);
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	char prompt[] = "\nJE SUIS LE PROMPT: ";
	char buff[1 + 1];
	int res;

	while (1)
	{
		ft_putstr_fd(prompt, STDOUT_FILENO);
		read(STDIN_FILENO, buff, 2);
		if (buff[0] == '1')
			res = fork_subprocesses(1);
		else if (buff[0] == '2')
			res = fork_subprocesses(2);
		else if (buff[0] == '3')
			res = fork_subprocesses(3);
		else if (buff[0] == '4')
			res = fork_subprocesses(4);
		else
		{
			ft_putendl_fd("type 1 or 2", STDOUT_FILENO);
			continue;
		}
		ft_putnbr_fd(res, STDOUT_FILENO);
	}
	return (0);
}
