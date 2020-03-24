#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/*
   on passe en premier argument le nom d'un fichier qui va servir de "pipe"...
   le fils va ecrir dedans, le pere attendra que le fils ai finit pour executer
   a son tour.
   FILS ==> ls -l
   PERE ==> wc -c
  */

/*
lessons: write the path very carefully in execve
when the stdout has been changed, printf("does not work anymore!\n");
*/
void child(char *argv1)
{
	int fd_w;
	char *args[] = {"ls", "-l", NULL};
	int dup_res;

	if ((fd_w = open(argv1, O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
	{
		perror("Open");
		exit(EXIT_FAILURE);
	}
	close(STDOUT_FILENO);
	dup(fd_w);
	close(fd_w);
	write(STDOUT_FILENO, "dup_res is...\n", sizeof("dup_res is...\n"));
	execve("/bin/ls", args, NULL);
	exit(EXIT_SUCCESS);
}

void father(char *argv1)
{
	int fd;
	char *args[] = {"wc", "-c", NULL};
	int dup_res;

	if((fd = open(argv1, O_RDONLY)) == -1)
	{
		perror("Read");
		exit(EXIT_FAILURE);
	}
	close(STDIN_FILENO);
	dup_res = dup(fd); //duplicate the fd in the position of the stdin...
	printf("dup_res is : %d\n", dup_res);
	close(fd); //close the fd since it is useless (ducplicated above...)
	execve("/usr/bin/wc", args, NULL);
	exit(EXIT_SUCCESS);
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	int desc1, desc2;

	if (argc != 2)
	{
		printf("failed to provide one arg\n");
		return (1);
	}
	switch (fork())
	{
		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			child(argv[1]);
			break;
		default:
			wait(NULL);
			father(argv[1]);
			break;
	}
	return (0);
}
