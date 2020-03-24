#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/uio.h>
//for the errno:
#include <errno.h>

#define BUFFER_SIZE 10

extern int errno;

void my_handler(int num_sig)
{
	printf("sigpipe!!!\n");
}

/*
write:
   - writing in a fildescriptor that is closed (lets say we close the p[1] in
   both processes(child and parent)	==> it does nothing...
									==>well actually write returns -1 !!!
	we can get the error mesage doing so:
	if (bytes_wrote == -1)
		perror("mon message:"); ==> output: "mon message: Bad File descriptor"

   - writting in a pipe which has not a reading end opened anymore: ==> SIGPIPE
   signal is produced (and can be catched with signal()).
	once again we can get the error mesage doing so:
	if (bytes_wrote == -1)
		perror("mon message:"); ==> output: "mon message: Broken pipe"
		this time it mentino sthe pipe!

read:
	- reading in a fd that is not opened anymore (exemple: both writing ends of
	the pipe (in child and parent process) have benn closed.
	we can use perror("read failed");
		==> "read failed: Bad file descriptor"

	- reading from a pipe where ther is something that ben written, but in the
	meantine the writing end was closed
			==> the read behaves normally, until there is nothing left to read.
*/

void child_func(int d_write)
{
	char message[] = "hey salut, je suis ton fils, et j'ecris...";
	int wrote;

	printf("this is the child func/process\n");
	wrote = write(d_write, message, sizeof(message));
	close(d_write); //here we write in the pipe then we close the writng end...
	printf("bytes wrote: %d\n", wrote);
	exit(EXIT_SUCCESS);

	if (wrote == -1)
	{
		perror("mon message-->");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void father_func(int d_read)
{
	char buff[BUFFER_SIZE];
	char res_read;
	printf("this is the father func/process\n");
	while ((res_read = read(d_read, buff, BUFFER_SIZE)) > 0)
	{
		printf("here is what we read: [%s]\n", buff);
		sleep(1);
	}
	if (res_read == -1)
	{
		perror("read failed");
		exit(EXIT_FAILURE);
	}
	if (res_read == 0)
		printf("there was nothing to read\n");
	exit(EXIT_SUCCESS);
}

int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	int p_desc[2];
	pid_t pid;

	if (pipe(p_desc) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	signal(SIGPIPE, my_handler);
	switch(fork())
	{
		case -1:
			perror("fork failed");
			exit(EXIT_FAILURE);
			break;
		case 0: //child process, writing in the pipe...
			close(p_desc[0]);
			sleep(1);
			child_func(p_desc[1]);
			break;
		default:
			close(p_desc[1]);
			sleep(2);
			father_func(p_desc[0]);
			break;
	}
	write(12, "hey", sizeof("hey"));
	return (0);
}
