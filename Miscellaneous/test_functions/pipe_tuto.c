#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
//for the errno:
#include <errno.h>

void child_func(int fd_write)
{
	// ici fermer stdout, puis utiliser  dup (ou dup2) pour remplacer le fd=1 par
	// le fd que l'on recoit en parametre (l'entree du pipe ou l'on va ecrire)

	//ecrire dans le pipe....
	exit(EXIT_SUCCESS);
}
void father_func(int fd_read)
{
	// ici fermer stdin (fd = 0) puis dupliquer le fd qu'on recoit en parametre
	// il va prendre la valeur zero (premiere valeur dispo en partant de zero)
	// nore: on doit meme fermer fd_read car on l'a dupliquer.

	// lire dans le pipe...
	exit(EXIT_SUCCESS);
}


int	main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	pid_t pid;
	int pipe_descriptors[2];
	// pipe_descriptors[0] --> la sortie du pipe, la ou on va connecter notre
	// stdin pour y lire.
	// pipe_descriptors[1] --> "l'entree du pipe" la ou on va connecter notre
	// stdout pour y ecrire!


	if (pipe(pipe_descriptors) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}

	// si le resutlat du fork est > 0 on est dans le meme process (le processe
	//parent)
	// si le resultat est 0, on est dans le process fils (fils du parent).
	switch(fork())
	{
		case -1:
			perror("fork failed");
			exit(EXIT_FAILURE);
			break;
		case 0: //child process, will  be  writing in the pipe. we dont need
			// the reading end of the pipe opened in this process so we close it
			close(pipe_descriptors[0]);
			child_func(pipe_descriptors[1]);
			break;
		default:
			// parent process will be reading from the pipe (it has to be the
			// opposite of the child!
			close(pipe_descriptors[1]);
			father_func(pipe_descriptors[0]);
			break;
	}
	return (0);
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
		this time it mentions the pipe!

read:
	- reading in a fd that is not opened anymore (exemple: both writing ends of
	the pipe (in child and parent process) have been closed.
	we can use perror("read failed");
		==> "read failed: Bad file descriptor"

	- reading from a pipe where there is something that has been written, but in the
	meantine the writing end was closed
			==> the read behaves normally, until there is nothing left to read.
*/
